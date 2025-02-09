#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#include <argparse/argparse.hpp>

#include <cmath>
#include "collatzseq.h"


int main(int argc, char** argv)
{
    std::cout << "Multi-Threading Collatz Sequence Examiner, Author: eidelen" << std::endl << std::endl;


    // Parse input ...
    argparse::ArgumentParser collatzArgs("Collatz Sequence");
    collatzArgs.add_argument("start_range").help("Start range").scan<'u', unsigned int>();
    collatzArgs.add_argument("end_range").help("End range").scan<'u', unsigned int>();
    collatzArgs.add_argument("block_size").help("Computation Block size").scan<'u', unsigned int>();

    try
    {
        collatzArgs.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << collatzArgs;
        std::exit(1);
    }

    NumT startValue = collatzArgs.get<unsigned int>("start_range");
    NumT endValue = collatzArgs.get<unsigned int>("end_range");
    NumT blockSize = collatzArgs.get<unsigned int>("block_size");

    size_t nbrIterations = std::ceil((endValue - startValue) / ((double)blockSize));

    std::vector<NumT> maxSeq;

    for(size_t i = 0; i < nbrIterations; i++)
    {
        std::shared_ptr<Collatz> cmt(new MultiThreadCollatz(4));

        NumT iterStart = startValue + i * blockSize;
        NumT iterEnd = iterStart + blockSize - 1;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto seq = cmt->getLongestSequence(iterStart, iterEnd);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        /* Debug Output
        std::cout << "Start runtime tests of -- Collatz Multi Threading  --" << std::endl;
        std::cout << "Compute longest Collatz sequence between " << iterStart << " and " << iterEnd << " ..." << std::endl;
        std::cout << "The computation took " << duration.count() << " ms" << std::endl;
        */

        // check if new max was reached
        if(maxSeq.size() < seq.size())
        {
            maxSeq = seq;
            NumT maxValueInSeq = *std::max_element(maxSeq.begin(), maxSeq.end());
            std::cout << "Found new maximum sequence: n=" << maxSeq[0] << " , length=" << maxSeq.size() << " , maxValue=" << maxValueInSeq << std::endl;
        }

        double throughputNpMS = blockSize / ((double)duration.count());
        std::cout << "Progress: " << ((double)i+1)/nbrIterations*100.0 << "% ,  Throughput N/ms: " << throughputNpMS << std::endl;
    }

}
