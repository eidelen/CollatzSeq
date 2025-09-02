cmake_minimum_required(VERSION 3.20)
project(CollatzSeqBigInt)

set(CMAKE_CXX_STANDARD 20)

cmake_policy(SET CMP0167 OLD)
find_package(Boost REQUIRED)

add_library(CollatzBigIntLib STATIC collatzseq.cpp collatzseq.h)
target_link_libraries(CollatzBigIntLib PRIVATE Boost::boost)
target_include_directories(CollatzBigIntLib INTERFACE .)
target_include_directories(CollatzBigIntLib PRIVATE ${Boost_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

add_executable(CollatzBigIntMain csMain.cpp)
target_link_libraries(CollatzBigIntMain CollatzBigIntLib argparse)

# Test the Collatz sequence project
option(TESTCS "Test library" OFF)
IF(${TESTCS})
    MESSAGE(STATUS "Tests activated")

    # Download and build gtest
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        v1.15.2
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(runCSBigTests test/main.cpp test/test_cs.cpp)
    target_link_libraries(runCSBigTests CollatzBigIntLib gtest_main Boost::boost)
ENDIF()
