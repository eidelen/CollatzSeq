#ifndef COLLATZ_SEQ_H
#define COLLATZ_SEQ_H

#include <vector>
#include <unordered_map>
#include <cstdint>

#include <boost/multiprecision/cpp_int.hpp>

using NumT = boost::multiprecision::cpp_int;

/**
 * Computes a single Collatz sequence step.
 */
NumT step(const NumT& n);

class Collatz
{
public:
    virtual std::vector<NumT> getSequence(NumT n) = 0;
    virtual std::vector<NumT> getLongestSequence(NumT start, NumT end);
};

class SimpleCollatz: public Collatz
{
public:
    SimpleCollatz();
    ~SimpleCollatz();
    std::vector<NumT> getSequence(NumT n) override;
};

class RecursiveCollatz: public Collatz
{
public:
    RecursiveCollatz();
    ~RecursiveCollatz();
    std::vector<NumT> getSequence(NumT n) override;

private:
    static void getSequence(NumT n, std::vector<NumT>& seq);
};

class HashCollatz: public SimpleCollatz
{
public:
    HashCollatz();
    ~HashCollatz();
    std::vector<NumT> getLongestSequence(NumT start, NumT end) override;

private:
    size_t getNStoreDepth(NumT n);
    std::unordered_map<NumT, size_t> mem;
};


class MultiThreadCollatz : public Collatz
{
public:
    // Constructor takes the number of threads to be used.
    MultiThreadCollatz(size_t nThreads);
    ~MultiThreadCollatz();

    // Return the full Collatz sequence for a single number n
    // (similar to SimpleCollatz).
    std::vector<NumT> getSequence(NumT n) override;

    // Find the longest Collatz sequence in the range [start, end] using nThreads.
    std::vector<NumT> getLongestSequence(NumT start, NumT end) override;

private:
    void processRange(size_t index, NumT rangeStart, NumT rangeEnd, std::vector<std::pair<size_t, NumT>>& threadResults);
    size_t nThreads;
};

#endif
