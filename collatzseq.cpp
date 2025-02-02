#include "collatzseq.h"

unsigned int step(const unsigned int& n)
{
    if(n % 2 == 0)
        return n/2;
    else
        return 3*n + 1;
}

SimpleCollatz::SimpleCollatz()
{
}

SimpleCollatz::~SimpleCollatz()
{
}

std::vector<unsigned int> SimpleCollatz::getSequence(unsigned int n)
{
    std::vector<unsigned int> seq;
    seq.push_back(n);
    while(n != 1)
    {
        n = step(n);
        seq.push_back(n);
    }
    return seq;
}

std::vector<unsigned int> SimpleCollatz::getLongestSequence(unsigned int start, unsigned int end)
{
    std::vector<unsigned int> longestSeq;
    for(unsigned int n = start; n < end + 1; n++)
    {
        auto seq = getSequence(n);
        if(seq.size() > longestSeq.size())
        {
            longestSeq = seq;
        }
    }

    return longestSeq;
}
