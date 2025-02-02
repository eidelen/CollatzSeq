#ifndef COLLATZ_SEQ_H
#define COLLATZ_SEQ_H

#include <vector>

/**
 * Computes a single Collatz sequence step.
 */
unsigned int step(const unsigned int& n);

class Collatz
{
public:
    virtual std::vector<unsigned int> getSequence(unsigned int n) = 0;
    virtual std::vector<unsigned int> getLongestSequence(unsigned int start, unsigned int end) = 0;
};

class SimpleCollatz: public Collatz
{
public:
    SimpleCollatz();
    ~SimpleCollatz();
    std::vector<unsigned int> getSequence(unsigned int n) override;
    std::vector<unsigned int> getLongestSequence(unsigned int start, unsigned int end) override;
};

#endif
