//
// Created by shiro on 01.08.19.
//
#include "gtest/gtest.h"
#include "../include/DataLoader.h"


class DataLoaderFixture : public  ::testing::Test
{
public:

protected:
    virtual void TearDown() {
     }

    virtual void SetUp() {

    }



};





TEST_F(DataLoaderFixture, universeTest){
    EXPECT_EQ(0,0);
}

TEST_F(DataLoaderFixture, getXValueTest)
{
    DataLoader loader{"get_x_test.txt"};
    EXPECT_EQ(loader.getXValue(), 23);
}

TEST_F(DataLoaderFixture, getExpressionTest)
{
    DataLoader loader{"get_expression_test.txt"};
    EXPECT_EQ(loader.getExpressionString(), "++3 2 - 2 x");
}

TEST_F(DataLoaderFixture, missingXTest)
{

}
TEST_F(DataLoaderFixture, invalidExpressionTest)
{
    
}