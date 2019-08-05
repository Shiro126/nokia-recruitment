#include <utility>

//
// Created by shiro on 03.08.19.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PrefixExpression.h"
#include "InvalidExpressionError.h"
class PrefixExpressionFixture : ::testing::Test {};

TEST(ExpressionTest, ExpressionTest_CalculationWithX_Test) {
    PrefixExpression expression{"+ x - 2 3"};
    expression.setX(5);

    EXPECT_EQ(expression.calculate(), 4);
}


TEST(ExpressionTest, ExpressionTest_Calculate_Test) {
    PrefixExpression expression{"* 2 + 1 - 3 / 3 3"};
    EXPECT_EQ(expression.calculate(), 6);
}


TEST(ExpressionTest, ExpressionTest_InvalidExpression1_Test) {
    EXPECT_THROW(PrefixExpression  expression{"++-"}, InvalidExpressionError);
}

TEST(ExpressionTest, ExpressionTest_InvalidExpression2_Test) {
    EXPECT_THROW(PrefixExpression{" "}, InvalidExpressionError);
}


TEST(ExpressionTest, ExpressionTest_Print_Test) {
    PrefixExpression expression{"++2 3 * 22 3"};
    std::stringstream ss;
    expression.print(ss);
    EXPECT_EQ(ss.str(),"+ + 2 3 * 22 3 ");
}


TEST(ExpressionTest, ExpressionTest_PrintInStandardWithoutBrackets_Test) {
    PrefixExpression expression{"++2 3 * 22 3"};
    std::stringstream ss;
    expression.printInStandard(ss);
    EXPECT_EQ(ss.str(),"2 + 3 + 22 * 3 ");
}

TEST(ExpressionTest, ExpressionTest_PrintInStandardWithBracketsMul_Test) {
    PrefixExpression expression{"*+2 3 + 22 3"};
    std::stringstream ss;
    expression.printInStandard(ss);
    EXPECT_EQ(ss.str(),"( 2 + 3 ) * ( 22 + 3 ) ");
}

TEST(ExpressionTest, ExpressionTest_PrintInStandardWithBracketsDiv_Test) {
    PrefixExpression expression{"/+2 3 + 22 3"};
    std::stringstream ss;
    expression.printInStandard(ss);
    EXPECT_EQ(ss.str(),"( 2 + 3 ) / ( 22 + 3 ) ");
}



