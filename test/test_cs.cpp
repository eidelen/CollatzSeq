#include <gtest/gtest.h>
#include "collatzseq.h"

TEST(Collatz, Step)
{
    ASSERT_EQ(step(4), 2);
    ASSERT_EQ(step(2), 1);
    ASSERT_EQ(step(1), 4);
}
