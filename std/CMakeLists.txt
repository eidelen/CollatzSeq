cmake_minimum_required(VERSION 3.20)
project(CollatzSeqStd)

set(CMAKE_CXX_STANDARD 20)

add_library(CollatzStdLib STATIC collatzseq.cpp collatzseq.h)
target_include_directories(CollatzStdLib INTERFACE .)

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

add_executable(CollatzStdMain csMain.cpp)
target_link_libraries(CollatzStdMain CollatzStdLib argparse)

add_executable(ThreadingCollatzStdMain threadingMain.cpp)
target_link_libraries(ThreadingCollatzStdMain CollatzStdLib argparse)

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

    add_executable(runCSTests test/main.cpp test/test_cs.cpp)
    target_link_libraries(runCSTests CollatzStdLib gtest_main)
ENDIF()
