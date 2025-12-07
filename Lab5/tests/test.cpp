#include <gtest/gtest.h>
#include "queue.h"

// Базовый тест: создание очереди
TEST(QueueTests, ConstructorCreatesEmptyQueue) {
    Queue<int> q(10);
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_EQ(q.capacity(), 10);
}

// Тест push()
TEST(QueueTests, PushIncreasesSize) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    EXPECT_EQ(q.size(), 2);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.front(), 1);
}

// Тест pop()
TEST(QueueTests, PopRemovesElementsInFIFOOrder) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.front(), 1);
    q.pop();
    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_EQ(q.front(), 3);
    q.pop();
    EXPECT_TRUE(q.empty());
}

// Тест front() const/non-const
TEST(QueueTests, FrontReturnsReference) {
    Queue<int> q(2);
    q.push(42);
    int &ref = q.front();
    EXPECT_EQ(ref, 42);
    ref = 100;
    EXPECT_EQ(q.front(), 100);
}

// Тест clear()
TEST(QueueTests, ClearResetsQueue) {
    Queue<int> q(5);
    q.push(1);
    q.push(2);
    q.push(3);
    q.clear();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

// Тест итератора
TEST(QueueTests, IteratorTraversesInOrder) {
    Queue<int> q(5);
    q.push(10);
    q.push(20);
    q.push(30);

    std::vector<int> values;
    for (auto it = q.begin(); it != q.end(); ++it) {
        values.push_back(*it);
    }

    ASSERT_EQ(values.size(), 3);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
}

// Тест постфиксного инкремента итератора
TEST(QueueTests, IteratorPostfixIncrement) {
    Queue<int> q(3);
    q.push(5);
    q.push(6);

    auto it = q.begin();
    auto old = it++;

    EXPECT_EQ(*old, 5);
    EXPECT_EQ(*it, 6);
}
