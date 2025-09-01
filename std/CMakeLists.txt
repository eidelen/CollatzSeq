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
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(runCSTests test/main.cpp test/test_cs.cpp)
    target_link_libraries(runCSTests CollatzStdLib gtest_main)
ENDIF()
