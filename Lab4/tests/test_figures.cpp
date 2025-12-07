#include <gtest/gtest.h>
#include "point.hpp"
#include "figure.hpp"
#include "trapezium.hpp"
#include "rhombus.hpp"
#include "pentagram.hpp"

TEST(FigureTest, PointAreaCalculation) {
    // Тест для квадрата 2x2
    Array<Point<double>> square_points{
        Point<double>(0, 0),
        Point<double>(2, 0),
        Point<double>(2, 2),
        Point<double>(0, 2)
    };
    
    class TestFigure : public Figure<double> {
    public:
        TestFigure(const Array<Point<double>>& points) : Figure<double>(points) {}
        size_t VerticesCount() const override { return 4; }
    };
    
    TestFigure square(square_points);
    EXPECT_NEAR(square.getArea(), 4.0, 1e-9);
}

TEST(FigureTest, TriangleArea) {
    // Треугольник с основанием 4 и высотой 3
    Array<Point<double>> triangle_points{
        Point<double>(0, 0),
        Point<double>(4, 0),
        Point<double>(2, 3)
    };
    
    class Triangle : public Figure<double> {
    public:
        Triangle(const Array<Point<double>>& points) : Figure<double>(points) {}
        size_t VerticesCount() const override { return 3; }
    };
    
    Triangle triangle(triangle_points);
    EXPECT_NEAR(triangle.getArea(), 6.0, 1e-9);
}

TEST(FigureTest, CenterCalculation) {
    Array<Point<double>> points{
        Point<double>(0, 0),
        Point<double>(4, 0),
        Point<double>(4, 4),
        Point<double>(0, 4)
    };
    
    class Square : public Figure<double> {
    public:
        Square(const Array<Point<double>>& points) : Figure<double>(points) {}
        size_t VerticesCount() const override { return 4; }
    };
    
    Square square(points);
    Point<double> center = square.getCenter();
    EXPECT_NEAR(center.x, 2.0, 1e-9);
    EXPECT_NEAR(center.y, 2.0, 1e-9);
}

TEST(FigureTest, EqualityOperator) {
    Array<Point<double>> points1{
        Point<double>(0, 0),
        Point<double>(1, 0),
        Point<double>(1, 1),
        Point<double>(0, 1)
    };
    
    Array<Point<double>> points2{
        Point<double>(0, 0),
        Point<double>(1, 0),
        Point<double>(1, 1),
        Point<double>(0, 1)
    };
    
    class TestFigure : public Figure<double> {
    public:
        TestFigure(const Array<Point<double>>& points) : Figure<double>(points) {}
        size_t VerticesCount() const override { return 4; }
    };
    
    TestFigure fig1(points1);
    TestFigure fig2(points2);
    
    EXPECT_TRUE(fig1 == fig2);
}

TEST(TrapeziumTest, CreationAndArea) {
    // Равнобедренная трапеция
    Trapezium<double> trap;
    // Здесь можно добавить тест с конкретными координатами
    EXPECT_EQ(trap.VerticesCount(), 4);
}

TEST(RhombusTest, Creation) {
    Rhombus<double> rhombus;
    EXPECT_EQ(rhombus.VerticesCount(), 4);
}

TEST(PentagramTest, Creation) {
    Pentagram<double> pentagram;
    EXPECT_EQ(pentagram.VerticesCount(), 5);
}