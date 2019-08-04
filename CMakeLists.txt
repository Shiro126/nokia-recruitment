cmake_minimum_required(VERSION 3.13)
project(PrefixNotationParser)

set(CMAKE_CXX_STANDARD 17)

# Miejsca w których kompilator ma szukać plików nagłówkowych .h i .hpp
include_directories(include                     #nasz folder include
        googletest-master/googlemock/include    #foldery google test
        googletest-master/googletest/include)

set(SOURCE_FILES
        src/DataLoader.cpp
        src/PrefixExpression.cpp src/Node.cpp)

set(TEST_SOURCES
        tests/main_test.cpp
        tests/DataLoaderTest.cpp
        tests/NodeTest.cpp tests/PrefixExpressionTest.cpp)

add_subdirectory(googletest-master)
link_libraries(gmock)

add_executable(PrefixNotationParser ${SOURCE_FILES} main.cpp)

add_executable(PrefixTest ${SOURCE_FILES} ${TEST_SOURCES})

