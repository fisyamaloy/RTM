#include <gtest/gtest.h>

#include <iostream>

#include "Vector.hpp"

TEST(ConstructorTest, DefaultConstructor)
{
    Danils::Vector<int> vec;
    EXPECT_NE(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
}

TEST(ConstructorTest, InitListConstructor)
{
    Danils::Vector<int> A = {1, 30, -5, -23, 7};
    ASSERT_TRUE(A.capacity() == 10);
    ASSERT_TRUE(A.size() == 5);

    ASSERT_TRUE(A[0] == 1);
    ASSERT_TRUE(A[1] == 30);
    ASSERT_TRUE(A[2] == -5);
    ASSERT_TRUE(A[3] == -23);
    ASSERT_TRUE(A[4] == 7);
}

TEST(ConstructorTest, CopyConstructor)
{
    Danils::Vector<int> A = {-20, 20, -40, 40, 7, 0};
    Danils::Vector<int> B = A;

    EXPECT_EQ(A.capacity(), B.capacity());
    EXPECT_EQ(A.size(), B.size());

    ASSERT_TRUE(A[0] == B[0]);
    ASSERT_TRUE(A[1] == B[1]);
    ASSERT_TRUE(A[2] == B[2]);
    ASSERT_TRUE(A[3] == B[3]);
    ASSERT_TRUE(A[4] == B[4]);
    ASSERT_TRUE(A[5] == B[5]);
    ASSERT_TRUE(A[6] == B[6]);
}

TEST(ConstructorTest, lengthParamConstructor)
{
    Danils::Vector<double> vec(22);
    EXPECT_EQ(vec.capacity(), 44);
    EXPECT_EQ(vec.size(), 22);
}

TEST(FunctionTest, atThrownException)
{
    Danils::Vector<int> vec{1, 3, 5, 10};
    EXPECT_THROW(vec.at(5), Danils::VectorException);
    EXPECT_THROW(vec.at(5), std::exception);
    EXPECT_THROW(vec.at(-1), Danils::VectorException);
    EXPECT_THROW(vec.at(-1), std::exception);
}

TEST(FunctionTest, atNotThrownException)
{
    Danils::Vector<int> vec{1, 3, 5, 10};
    EXPECT_NO_THROW(vec.at(0));
    EXPECT_NO_THROW(vec.at(1));
    EXPECT_NO_THROW(vec.at(2));
    EXPECT_NO_THROW(vec.at(3));
}

TEST(FunctionTest, at)
{
    Danils::Vector<int> vec{1, 3, 5, 10};
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 3);
    EXPECT_EQ(vec.at(2), 5);
    EXPECT_EQ(vec.at(3), 10);
}

TEST(FunctionTest, push_back)
{
    Danils::Vector<const char*> vec{"Hel", "lo", "wo"};
    vec.push_back("rl");
    vec.push_back("d");
    vec.push_back("I'm");
    vec.push_back("good");

    EXPECT_EQ(vec.size(), 7);
    EXPECT_EQ(vec.capacity(), 12);

    ASSERT_STREQ(vec[0], "Hel");
    ASSERT_STREQ(vec[1], "lo");
    ASSERT_STREQ(vec[2], "wo");
    ASSERT_STREQ(vec[3], "rl");
    ASSERT_STREQ(vec[4], "d");
    ASSERT_STREQ(vec[5], "I'm");
    ASSERT_STREQ(vec[6], "good");
}

TEST(FunctionTest, push_front)
{
    Danils::Vector<bool> vec = {true, true, true};
    vec.push_front(false);  // vec[1]
    vec.push_front(true);   // vec[0]

    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(vec.capacity(), 6);
    ASSERT_EQ(vec[0], true);
    ASSERT_EQ(vec[1], false);
    ASSERT_EQ(vec[2], true);
    ASSERT_EQ(vec[3], true);
    ASSERT_EQ(vec[4], true);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
