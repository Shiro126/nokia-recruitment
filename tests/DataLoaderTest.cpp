//
// Created by shiro on 01.08.19.
//
#include "gtest/gtest.h"
#include "../include/DataLoader.h"


class DataLoaderFixture : public  ::testing::Test
{
    std::unique_ptr<DataLoader> loader{};
protected:
    virtual void SetUp() {

        loader = std::make_unique<DataLoader>("test.txt");
    }

    virtual void TearDown() {

    }
};





TEST_F(DataLoaderFixture, universeTest){
    EXPECT_EQ(0,0);
}

TEST_F(DataLoaderFixture, getXValueTest)
{

}

TEST_F(DataLoaderFixture, getExpressionTest)
{

}

TEST_F(DataLoaderFixture, initTest)
{

}
