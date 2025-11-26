#include <gtest/gtest.h>
#include "point.hpp"

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 2.1);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 2.1);
}

TEST(PointTest, CopyConstructor) {
    Point<float> p1(1.0f, 2.0f);
    Point<float> p2(p1);
    EXPECT_FLOAT_EQ(p2.x, 1.0f);
    EXPECT_FLOAT_EQ(p2.y, 2.0f);
}

TEST(PointTest, EqualityOperator) {
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(3, 4);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, InequalityOperator) {
    Point<int> p1(1, 2);
    Point<int> p2(3, 4);
    
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 != p1);
}

TEST(PointTest, OutputOperator) {
    Point<int> p(5, 10);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "(5; 10)");
}

TEST(PointTest, InputOperator) {
    Point<double> p;
    std::stringstream ss("3.14 2.71");
    ss >> p;
    EXPECT_DOUBLE_EQ(p.x, 3.14);
    EXPECT_DOUBLE_EQ(p.y, 2.71);
}