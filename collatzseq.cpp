#include "collatzseq.h"

unsigned int step(const unsigned int& n)
{
    if(n % 2 == 0)
        return n/2;
    else
        return 3*n + 1;
}
