#include <gtest/gtest.h>
#include "array.hpp"

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_GE(arr.getCapacity(), 1);
}

TEST(ArrayTest, SizeConstructor) {
    Array<double> arr(5);
    EXPECT_EQ(arr.getSize(), 5);
}

TEST(ArrayTest, InitializerListConstructor) {
    Array<int> arr{1, 2, 3, 4, 5};
    EXPECT_EQ(arr.getSize(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, PushBack) {
    Array<int> arr;
    arr.push(10);
    arr.push(20);
    
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1{1, 2, 3};
    Array<int> arr2(arr1);
    
    EXPECT_EQ(arr2.getSize(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1{1, 2, 3};
    Array<int> arr2(std::move(arr1));
    
    EXPECT_EQ(arr2.getSize(), 3);
    EXPECT_EQ(arr1.getSize(), 0); // После move исходный пустой
}

TEST(ArrayTest, AssignmentOperator) {
    Array<int> arr1{1, 2, 3};
    Array<int> arr2;
    arr2 = arr1;
    
    EXPECT_EQ(arr2.getSize(), 3);
    EXPECT_EQ(arr2[1], 2);
}

TEST(ArrayTest, AccessOperator) {
    Array<std::string> arr{"hello", "world"};
    EXPECT_EQ(arr[0], "hello");
    EXPECT_EQ(arr[1], "world");
}

TEST(ArrayTest, ConstAccessOperator) {
    const Array<int> arr{1, 2, 3};
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, OutOfRangeAccess) {
    Array<int> arr{1, 2, 3};
    EXPECT_THROW(arr[5], std::out_of_range);
}

TEST(ArrayTest, Pop) {
    Array<int> arr{1, 2, 3};
    arr.pop();
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[1], 2);
}

TEST(ArrayTest, PopEmpty) {
    Array<int> arr;
    EXPECT_THROW(arr.pop(), std::out_of_range);
}

TEST(ArrayTest, InsertAt) {
    Array<int> arr{1, 3, 4};
    arr.insertAt(1, 2);
    
    EXPECT_EQ(arr.getSize(), 4);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, RemoveAt) {
    Array<int> arr{1, 2, 3, 4};
    arr.removeAt(1);
    
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, Resize) {
    Array<int> arr{1, 2, 3};
    arr.resize(5);
    EXPECT_EQ(arr.getSize(), 5);
    
    arr.resize(2);
    EXPECT_EQ(arr.getSize(), 2);
}