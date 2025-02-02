cmake_minimum_required(VERSION 3.9)
project(CollatzSeq)

set(CMAKE_CXX_STANDARD 20)

add_library(CollatzLib STATIC collatzseq.cpp collatzseq.h)
target_include_directories(CollatzLib INTERFACE .)
#target_compile_features(PointSetsFitting PUBLIC cxx_std_17)

add_executable(CollatzMain csMain.cpp)
target_link_libraries(CollatzMain CollatzLib)

# Test the Collatz sequence project
option(TESTCS "Test library" OFF)
IF(${TESTCS})
    MESSAGE(STATUS "Tests activated")

    # Download and build gtest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(runCSTests test/main.cpp test/test_cs.cpp)
    target_link_libraries(runCSTests CollatzLib gtest_main)
ENDIF()
