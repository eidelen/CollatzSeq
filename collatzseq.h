#ifndef COLLATZ_SEQ_H
#define COLLATZ_SEQ_H

#include <vector>
#include <unordered_map>

/**
 * Computes a single Collatz sequence step.
 */
unsigned int step(const unsigned int& n);

class Collatz
{
public:
    virtual std::vector<unsigned int> getSequence(unsigned int n) = 0;
    virtual std::vector<unsigned int> getLongestSequence(unsigned int start, unsigned int end);
};

class SimpleCollatz: public Collatz
{
public:
    SimpleCollatz();
    ~SimpleCollatz();
    std::vector<unsigned int> getSequence(unsigned int n) override;
};

class RecursiveCollatz: public Collatz
{
public:
    RecursiveCollatz();
    ~RecursiveCollatz();
    std::vector<unsigned int> getSequence(unsigned int n) override;

private:
    static void getSequence(unsigned int n, std::vector<unsigned int>& seq);
};

class HashCollatz: public SimpleCollatz
{
public:
    HashCollatz();
    ~HashCollatz();
    std::vector<unsigned int> getLongestSequence(unsigned int start, unsigned int end) override;

private:
    size_t getNStoreDepth(const unsigned int &n);
    std::unordered_map<unsigned int, size_t> mem;
};

#endif
