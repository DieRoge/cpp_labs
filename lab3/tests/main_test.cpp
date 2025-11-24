#include <gtest/gtest.h>

#include "point.h"
#include "vector-points.h"
#include "figure.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"
#include "vector-figure.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TriangleTest, AreaCalculation) {
    Point p1(0, 0);
    Point p2(1, 0);
    Point p3(0, 1);
    Triangle tri(p1, p2, p3);
    EXPECT_NEAR(static_cast<double>(tri.Area()), 0.5, 1e-10);
}

TEST(TriangleTest, CenterCalculation) {
    Point p1(0, 0);
    Point p2(2, 0);
    Point p3(0, 2);
    Triangle tri(p1, p2, p3);
    Point center = tri.Center();
    EXPECT_EQ(center.x, 0);
    EXPECT_EQ(center.y, 0);
}
TEST(HexagonTest, AreaCalculation) {
    Point p1(0, 0);
    Point p2(2, 0);
    Point p3(3, 1);
    Point p4(2, 2);
    Point p5(0, 2);
    Point p6(-1, 1);
    Hexagon h(p1, p2, p3, p4, p5, p6);
    EXPECT_NEAR(static_cast<double>(h.Area()), 6.0, 1e-10);
}

TEST(HexagonTest, CenterCalculation) {
    Point p1(0, 0);
    Point p2(2, 0);
    Point p3(3, 1);
    Point p4(2, 2);
    Point p5(0, 2);
    Point p6(-1, 1);
    Hexagon h(p1, p2, p3, p4, p5, p6);
    Point center = h.Center();
    EXPECT_EQ(center.x, 1);
    EXPECT_EQ(center.y, 1);
}

TEST(OctagonTest, AreaCalculation) {
    Point p1(0, 1);
    Point p2(1, 0);
    Point p3(3, 0);
    Point p4(4, 1);
    Point p5(4, 3);
    Point p6(3, 4);
    Point p7(1, 4);
    Point p8(0, 3);
    Octagon o(p1, p2, p3, p4, p5, p6, p7, p8);
    EXPECT_NEAR(static_cast<double>(o.Area()), 14.0, 1e-10);
}

TEST(OctagonTest, CenterCalculation) {
    Point p1(0, 1);
    Point p2(1, 0);
    Point p3(3, 0);
    Point p4(4, 1);
    Point p5(4, 3);
    Point p6(3, 4);
    Point p7(1, 4);
    Point p8(0, 3);
    Octagon o(p1, p2, p3, p4, p5, p6, p7, p8);
    Point center = o.Center();
    EXPECT_EQ(center.x, 2);
    EXPECT_EQ(center.y, 2);
}

TEST(FigureTest, EqualityOperator) {
    Hexagon h1(Point(0, 0), Point(2, 0), Point(3, 1), Point(2, 2), Point(0, 2), Point(-1, 1));
    Hexagon h2(Point(0, 0), Point(2, 0), Point(3, 1), Point(2, 2), Point(0, 2), Point(-1, 1));
    Hexagon h3(Point(1, 1), Point(3, 1), Point(4, 2), Point(3, 3), Point(1, 3), Point(0, 2));
    
    EXPECT_TRUE(h1 == h2);
    EXPECT_FALSE(h1 == h3);
    EXPECT_TRUE(h1 != h3);
}

TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(3, 4);
    EXPECT_EQ(p.x, 3);
    EXPECT_EQ(p.y, 4);
}

TEST(PointTest, EqualityOperator) {
    Point p1(1, 2);
    Point p2(1, 2);
    Point p3(2, 2);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(VectorPointsTest, AddAndGetPoints) {
    VectorPoints vp;
    Point p1(1, 2);
    Point p2(3, 4);
    vp.push(p1);
    vp.push(p2);
    EXPECT_EQ(vp.len(), 2);
    EXPECT_TRUE(vp[0] == p1);
    EXPECT_TRUE(vp[1] == p2);
}

TEST(VectorPointsTest, SetAndGet) {
    VectorPoints vp;
    vp.push(Point(0, 0));
    vp.push(Point(0, 0));
    vp.set(0, Point(5, 5));
    vp.set(1, Point(7, 9));
    EXPECT_EQ(vp[0].x, 5);
    EXPECT_EQ(vp[0].y, 5);
    EXPECT_EQ(vp[1].x, 7);
    EXPECT_EQ(vp[1].y, 9);
}

TEST(VectorFigureTest, AddAndGetFigures) {
    VectorFigure vf;
    Triangle* tri = new Triangle(Point(0, 0), Point(1, 0), Point(0, 1));
    Hexagon* hx = new Hexagon(Point(0, 0), Point(2, 0), Point(3, 1), Point(2, 2), Point(0, 2), Point(-1, 1));
    
    vf.push(tri);
    vf.push(hx);
    
    EXPECT_EQ(vf.len(), 2);
    EXPECT_NEAR(static_cast<double>(vf[0]->Area()), 0.5, 1e-10);
    EXPECT_NEAR(static_cast<double>(vf[1]->Area()), 6.0, 1e-10);
}

TEST(VectorFigureTest, EraseFunction) {
    VectorFigure vf;
    vf.push(new Triangle(Point(0, 0), Point(1, 0), Point(0, 1)));
    vf.push(new Hexagon(Point(0, 0), Point(2, 0), Point(3, 1), Point(2, 2), Point(0, 2), Point(-1, 1)));
    vf.push(new Octagon(Point(0, 1), Point(1, 0), Point(3, 0), Point(4, 1), Point(4, 3), Point(3, 4), Point(1, 4), Point(0, 3)));
    
    EXPECT_EQ(vf.len(), 3);
    
    vf.erase(1);
    EXPECT_EQ(vf.len(), 2);
    
    EXPECT_NEAR(static_cast<double>(vf[0]->Area()), 0.5, 1e-10);
    EXPECT_NEAR(static_cast<double>(vf[1]->Area()), 14.0, 1e-10);
}
