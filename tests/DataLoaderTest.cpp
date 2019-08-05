//
// Created by shiro on 01.08.19.
//
#include "gtest/gtest.h"
#include "../include/DataLoader.h"
#include "InvalidExpressionError.h"



TEST(DataLoaderTest, getXValueTest)
{
    DataLoader loader{"test_data/get_x_test.txt"};
    EXPECT_EQ(loader.getXValue(), 23);
}

TEST(DataLoaderTest, getExpressionTest)
{
    DataLoader loader{"test_data/get_expression_test.txt"};
    EXPECT_EQ(loader.getExpressionString(), "++3 2 - 2 x");
}

TEST(DataLoaderTest, missingXTest)
{
    EXPECT_THROW(DataLoader loader{"test_data/invalid_no_x.txt"}, InvalidExpressionError);

}

TEST(DataLoaderTest, illegalCharactersTest)
{

    EXPECT_THROW(DataLoader loader{"test_data/invalid_illegal_characters.txt"}, InvalidExpressionError);

}