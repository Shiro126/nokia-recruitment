//
// Created by shiro on 02.08.19.
//
#include <gtest/gtest.h>
#include "Node.h"

class NodeFixture : public ::testing::Test {

};

TEST_F(NodeFixture, NodeFixture_NodeInit_Test) {
    Node node{"Init"};
    EXPECT_EQ("Init", node.getValue());
    EXPECT_EQ(nullptr, node.getRSon());
    EXPECT_EQ(nullptr, node.getLSon());
}

TEST_F(NodeFixture, NodeFixture_AccessSons_Test) {
    Node parent{"Init"};
    Node lSon{"LSon"};
    Node rSon{"RSon"};
    parent.setLSon(&lSon);
    parent.setRSon(&rSon);
    EXPECT_EQ("LSon", parent.getLSon()->getValue());
    EXPECT_EQ("RSon", parent.getRSon()->getValue());
}
