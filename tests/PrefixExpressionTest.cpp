#include <utility>

//
// Created by shiro on 03.08.19.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PrefixExpression.h"
#include "InvalidExpressionError.h"
/*
class MockDataLoader : public DataLoader {
public:
    MOCK_METHOD0(getXValue, int ());
    MOCK_CONST_METHOD0(getExpressionString, std::string &());

    void setData(std::string str, int x){
        xValue = x;
        expressionString = std::move(str);
    }
};
 */
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


TEST(ExpressionTest, SimplifyPlusMinusTest) {
    PrefixExpression expression{"+-2+2 0- 2 2"};
    expression.simplify();
    std::stringstream ss;
    expression.printInStandard(ss);
    EXPECT_EQ(ss.str(), "0 ");
}


TEST(ExpressionTest, SimplifyMulDivTest) {
    PrefixExpression expression{"*/0 2 * 1 * 6 1"};
    expression.simplify();
    std::stringstream ss;
    expression.printInStandard(ss);
    EXPECT_EQ(ss.str(), "0 ");
}

/*
TEST(ExpressionTest, DataLoaderMock) {
    MockDataLoader loader;
    PrefixExpression expression{};
    loader.setData( "+ 2 3", 5);
    EXPECT_CALL(loader, getXValue()).Times(1);
    EXPECT_CALL(loader, getExpressionString()).Times(1);
    expression.load(loader);

    EXPECT_EQ(expression.getXValue(), 5);
}
*/