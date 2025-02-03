#include "collatzseq.h"

unsigned int step(const unsigned int& n)
{
    if(n % 2 == 0)
        return n/2;
    else
        return 3*n + 1;
}


std::vector<unsigned int> Collatz::getLongestSequence(unsigned int start, unsigned int end)
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



RecursiveCollatz::RecursiveCollatz()
{

}

RecursiveCollatz::~RecursiveCollatz()
{

}

void RecursiveCollatz::getSequence(unsigned int n, std::vector<unsigned int> &seq)
{
    seq.push_back(n);

    if(n == 1)
        return;

    getSequence(step(n), seq);
}

std::vector<unsigned int> RecursiveCollatz::getSequence(unsigned int n)
{
    std::vector<unsigned int> seq;
    getSequence(n, seq);
    return seq;
}



HashCollatz::HashCollatz()
{

}

HashCollatz::~HashCollatz()
{

}

void HashCollatz::getSequence(unsigned int n, std::vector<unsigned int> &seq)
{
    seq.push_back(n);

    if(n == 1)
        return;

    // check if value was already computed
    //if(mem.find(n) == mem.end())
    //{
        getSequence(step(n), seq);
    //}
}


std::vector<unsigned int> HashCollatz::getSequence(unsigned int n)
{
    std::vector<unsigned int> seq;
    getSequence(n, seq);
    return seq;
}

