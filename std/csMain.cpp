#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#include <argparse/argparse.hpp>

#include "collatzseq.h"


int main(int argc, char** argv)
{
    std::cout << "Collatz Sequence Examiner, Author: eidelen" << std::endl << std::endl;


    // Parse input ...
    argparse::ArgumentParser collatzArgs("Collatz Sequence");
    collatzArgs.add_argument("start_range").help("Start range").scan<'i', unsigned int>();
    collatzArgs.add_argument("end_range").help("End range").scan<'i', unsigned int>();

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

    unsigned int startValue = collatzArgs.get<unsigned int>("start_range");
    unsigned int endValue = collatzArgs.get<unsigned int>("end_range");


    // Setup tests...
    std::vector< std::tuple<std::string, std::shared_ptr<Collatz>> > tests =
        { {"SimpleCollatz", std::shared_ptr<Collatz>(new SimpleCollatz())},
          {"RecursiveCollatz", std::shared_ptr<Collatz>(new RecursiveCollatz())},
          {"HashCollatz", std::shared_ptr<Collatz>(new HashCollatz())},
          {"MultiThreadCollatz", std::shared_ptr<Collatz>(new MultiThreadCollatz(4))}};


    // Execute tests...
    for( auto[name, col]: tests )
    {
        std::cout << "Start runtime tests of -- " << name << " --" << std::endl;
        std::cout << "Compute longest Collatz sequence between " << startValue << " and " << endValue << " ..." << std::endl;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto seq = col->getLongestSequence(startValue, endValue);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        size_t sequenceLength = seq.size();
        unsigned int maxValueInSeq = *std::max_element(seq.begin(), seq.end());

        std::cout << "The longest sequence starts with " << seq[0] << ", reaches the max value " << maxValueInSeq << " and has the length of " << sequenceLength << std::endl;
        std::cout << "The computation took " << duration.count() << " ms" << std::endl << std::endl;
    }
}
