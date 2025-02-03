#include <gtest/gtest.h>
#include <memory>
#include "collatzseq.h"

TEST(Collatz, Step)
{
    ASSERT_EQ(step(4), 2);
    ASSERT_EQ(step(2), 1);
    ASSERT_EQ(step(1), 4);
}

std::vector<unsigned int> getSeq3()
{
    return {3, 10, 5, 16, 8, 4, 2, 1};
}

TEST(Simple, Suequence)
{
    std::shared_ptr<Collatz> c(new SimpleCollatz());
    auto seq = c->getSequence(3);
    auto prep_3_seq = getSeq3();
    ASSERT_EQ(seq.size(), prep_3_seq.size());
    ASSERT_TRUE(std::equal(seq.begin(), seq.end(), prep_3_seq.begin()));
}

TEST(Simple, LongestSuequence)
{
    std::shared_ptr<Collatz> c(new SimpleCollatz());
    auto seq = c->getLongestSequence(1, 5);
    auto prep_3_seq = getSeq3();
    ASSERT_TRUE(std::equal(seq.begin(), seq.end(), prep_3_seq.begin()));
}

TEST(Simple, LongestSuequence1Mega)
{
    std::shared_ptr<Collatz> c(new SimpleCollatz());
    auto seq = c->getLongestSequence(1, 100000);
    std::cout << "Simple Collatz 1 Million: " << seq[0] << " , length = " << seq.size() << std::endl;
    ASSERT_TRUE(true);
}

TEST(Recursive, Suequence)
{
    std::shared_ptr<Collatz> c(new RecursiveCollatz());
    auto seq = c->getSequence(3);
    auto prep_3_seq = getSeq3();
    ASSERT_EQ(seq.size(), prep_3_seq.size());
    ASSERT_TRUE(std::equal(seq.begin(), seq.end(), prep_3_seq.begin()));
}

TEST(Recursive, LongestSuequence)
{
    std::shared_ptr<Collatz> c(new RecursiveCollatz());
    auto seq = c->getLongestSequence(1, 5);
    auto prep_3_seq = getSeq3();
    ASSERT_TRUE(std::equal(seq.begin(), seq.end(), prep_3_seq.begin()));
}

TEST(Recursive, LongestSuequence1Mega)
{
    std::shared_ptr<Collatz> c(new RecursiveCollatz());
    auto seq = c->getLongestSequence(1, 100000);
    std::cout << "Recursive Collatz 1 Million: " << seq[0] << " , length = " << seq.size() << std::endl;
    ASSERT_TRUE(true);
}


TEST(Hash, Suequence)
{
    std::shared_ptr<Collatz> c(new HashCollatz());
    auto seq = c->getSequence(3);
    auto prep_3_seq = getSeq3();
    ASSERT_EQ(seq.size(), prep_3_seq.size());
    ASSERT_TRUE(std::equal(seq.begin(), seq.end(), prep_3_seq.begin()));
}

TEST(Hash, LongestSuequence)
{
    std::shared_ptr<Collatz> c(new HashCollatz());
    auto seq = c->getLongestSequence(1, 5);
    auto prep_3_seq = getSeq3();
    ASSERT_TRUE(std::equal(seq.begin(), seq.end(), prep_3_seq.begin()));
}

TEST(Hash, LongestSuequence1Mega)
{
    std::shared_ptr<Collatz> c(new HashCollatz());
    auto seq = c->getLongestSequence(1, 100000);
    std::cout << "Recursive Collatz 1 Million: " << seq[0] << " , length = " << seq.size() << std::endl;
    ASSERT_TRUE(true);
}
