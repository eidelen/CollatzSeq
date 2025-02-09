#include "collatzseq.h"


#include <thread>
#include <algorithm>
#include <utility>



inline NumT step(const NumT& n)
{
    if ((n & 1) == 0)  // bit operation to check if even
        return n >> 1; // instead of division by 2 just make bit operation
    else
        return 3*n + 1;
}


std::vector<NumT> Collatz::getLongestSequence(NumT start, NumT end)
{
    std::vector<NumT> longestSeq;
    for(NumT n = start; n < end + 1; n++)
    {
        const std::vector<NumT> seq = getSequence(n);
        if(seq.size() > longestSeq.size())
        {
            longestSeq = seq;
        }
    }

    return longestSeq;
}



SimpleCollatz::SimpleCollatz()
{
}

SimpleCollatz::~SimpleCollatz()
{
}

std::vector<NumT> SimpleCollatz::getSequence(NumT n)
{
    std::vector<NumT> seq;
    seq.reserve(4096);
    seq.push_back(n);
    while(n != 1)
    {
        n = step(n);
        seq.push_back(n);
    }
    return seq;
}

RecursiveCollatz::RecursiveCollatz()
{

}

RecursiveCollatz::~RecursiveCollatz()
{

}

void RecursiveCollatz::getSequence(NumT n, std::vector<NumT> &seq)
{
    seq.push_back(n);

    if(n == 1)
        return;

    getSequence(step(n), seq);
}

std::vector<NumT> RecursiveCollatz::getSequence(NumT n)
{
    std::vector<NumT> seq;
    getSequence(n, seq);
    return seq;
}



HashCollatz::HashCollatz()
{

}

HashCollatz::~HashCollatz()
{

}

std::vector<NumT> HashCollatz::getLongestSequence(NumT start, NumT end)
{
    size_t maxLength = 0;
    NumT maxLenN = start;

    // search just for longest
    for(NumT n = start; n < end + 1; n++)
    {
        size_t thisLen = getNStoreDepth(n);
        if(thisLen > maxLength)
        {
            maxLength = thisLen;
            maxLenN = n;
        }
    }

    // only called once - this is fast
    return getSequence(maxLenN);
}

size_t HashCollatz::getNStoreDepth(NumT n)
{
    if(n == 1)
        return 1;

    // cut the recursion - check if value was already computed
    if(mem.find(n) == mem.end())
    {
        size_t currentDepth = getNStoreDepth(step(n)) + 1;
        mem[n] = currentDepth;
        return currentDepth;
    }
    else
    {
        return mem[n];
    }
}


MultiThreadCollatz::MultiThreadCollatz(size_t nThreads)
    : nThreads(nThreads)
{
}

MultiThreadCollatz::~MultiThreadCollatz()
{
}

std::vector<NumT> MultiThreadCollatz::getSequence(NumT n)
{
    // Reuse the same iterative approach as SimpleCollatz
    std::vector<NumT> seq;
    seq.reserve(1000);  // optional reservation to avoid frequent reallocations
    seq.push_back(n);

    while (n != 1)
    {
        n = step(n);
        seq.push_back(n);
    }
    return seq;
}

void MultiThreadCollatz::processRange(size_t index, NumT rangeStart, NumT rangeEnd, std::vector<std::pair<size_t, NumT>>& threadResults)
{
    // Find the local best: (max sequence length, integer that yields max seq)
    size_t maxLen = 0;
    NumT bestN    = rangeStart;

    for (NumT n = rangeStart; n <= rangeEnd; ++n)
    {
        // Use the very normal getSequence, without any data structure
        const size_t seqLen = getSequence(n).size();
        if (seqLen > maxLen)
        {
            maxLen = seqLen;
            bestN  = n;
        }
    }

    // Store the results
    threadResults[index] = {maxLen, bestN};
}


std::vector<NumT> MultiThreadCollatz::getLongestSequence(NumT start, NumT end)
{
    // Compute thread input sizes
    const size_t totalRange = static_cast<size_t>(end - start + 1);
    const size_t baseSize   = totalRange / nThreads;
    const size_t remainder  = totalRange % nThreads;

    std::vector<std::pair<size_t, NumT>> threadResults(nThreads);

    std::vector<std::thread> workers;
    workers.reserve(nThreads);

    NumT currentStart = start;

    // Launch each thread on its sub-range
    for (size_t t = 0; t < nThreads; ++t)
    {
        const size_t thisChunkSize = baseSize + ((t < remainder) ? 1 : 0);

        NumT currentEnd = currentStart + thisChunkSize - 1;

        workers.emplace_back(&MultiThreadCollatz::processRange, this, t, currentStart, currentEnd, std::ref(threadResults));

        currentStart = currentEnd + 1;
    }

    // Join all threads
    for (auto &th : workers)
    {
        if (th.joinable())
        {
            th.join();
        }
    }

    // Find the overall best result among all threads
    auto it = std::max_element(threadResults.begin(), threadResults.end(), [](const std::pair<size_t, NumT> &a, const std::pair<size_t, NumT> &b) {
                    return a.first < b.first; });

    // Only called once
    return getSequence(it->second);
}
