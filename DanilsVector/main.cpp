#include <gtest/gtest.h>

#include <string>
#include <unordered_set>

#include "Vector.hpp"

struct Student
{
    unsigned short course;
    double         avarageGrade;
    std::string    name;

    Student() : course(0), avarageGrade(0), name("Unknown") {}

    Student(const unsigned short course, const double avarageGrade, const std::string& name)
        : course(course), avarageGrade(avarageGrade), name(name)
    {
    }

    Student(const Student& other)
    {
        this->course       = other.course;
        this->avarageGrade = other.avarageGrade;
        this->name         = other.name;
    }

    friend bool operator==(const Student& first, const Student& second)
    {
        return first.name == second.name && first.course == second.course &&
               Student::areAverageStudentsGradesEqual(first, second);
    }

    Student& operator=(const Student& other)
    {
        this->name         = other.name;
        this->course       = other.course;
        this->avarageGrade = other.avarageGrade;

        return *this;
    }

private:
    inline static bool areAverageStudentsGradesEqual(const Student& first, const Student& second)
    {
        return std::abs(first.avarageGrade - second.avarageGrade) <
               std::numeric_limits<double>::epsilon();
    }
};

// Fixture
struct TestStudent : testing::Test
{
    const Student DANIK = Student(3, 7.6, "Danik");
    const Student ANTON = Student(2, 8.5999, "Anton");
    const Student KATYA = Student(3, 7.334, "Katya");
    const Student YARIK = Student(4, 8.6, "Yarik");
    const Student NAZAR = Student(3, 7.6, "Nazar");

    Danils::Vector<Student> students = {DANIK, ANTON, KATYA, YARIK, NAZAR};
};

TEST(ConstructorTest, DefaultConstructor)
{
    Danils::Vector<int> vec;
    ASSERT_EQ(vec.capacity(), 20);
    ASSERT_EQ(vec.size(), 0);
}

TEST_F(TestStudent, DefaultConstructor)
{
    Danils::Vector<Student> vec;
    ASSERT_EQ(vec.capacity(), 20);
    ASSERT_EQ(vec.size(), 0);
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

TEST_F(TestStudent, CopyConstructor)
{
    Danils::Vector<Student> B = students;

    EXPECT_EQ(students.capacity(), B.capacity());
    EXPECT_EQ(students.size(), B.size());

    ASSERT_TRUE(students[0] == B[0]);
    ASSERT_TRUE(students[1] == B[1]);
    ASSERT_TRUE(students[2] == B[2]);
    ASSERT_TRUE(students[3] == B[3]);
    ASSERT_TRUE(students[4] == B[4]);
    ASSERT_TRUE(students[5] == B[5]);
    ASSERT_TRUE(students[6] == B[6]);
}

TEST(ConstructorTest, lengthParamConstructor)
{
    Danils::Vector<double> vec(22);
    EXPECT_EQ(vec.capacity(), 44);
    EXPECT_EQ(vec.size(), 22);
}

TEST_F(TestStudent, lengthParamConstructor)
{
    Danils::Vector<Student> A(13);
    ASSERT_TRUE(A.capacity() == 26);
    ASSERT_TRUE(A.size() == 13);
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

TEST_F(TestStudent, at)
{
    EXPECT_EQ(students.at(0), DANIK);
    EXPECT_EQ(students.at(1), ANTON);
    EXPECT_EQ(students.at(2), KATYA);
    EXPECT_EQ(students.at(3), YARIK);
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

TEST_F(TestStudent, push_back)
{
    Student newStudent(1, 10, "God");
    students.push_back(newStudent);

    EXPECT_EQ(students.size(), 6);
    EXPECT_EQ(students.capacity(), 10);

    EXPECT_EQ(students.at(0), DANIK);
    EXPECT_EQ(students.at(1), ANTON);
    EXPECT_EQ(students.at(2), KATYA);
    EXPECT_EQ(students.at(3), YARIK);
    EXPECT_EQ(students.at(4), NAZAR);
    EXPECT_EQ(students.at(5), newStudent);
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

TEST_F(TestStudent, push_front)
{
    Student newStudent(1, 10, "God");
    students.push_front(newStudent);

    EXPECT_EQ(students.size(), 6);
    EXPECT_EQ(students.capacity(), 10);

    EXPECT_EQ(students.at(0), newStudent);
    EXPECT_EQ(students.at(1), DANIK);
    EXPECT_EQ(students.at(2), ANTON);
    EXPECT_EQ(students.at(3), KATYA);
    EXPECT_EQ(students.at(4), YARIK);
    EXPECT_EQ(students.at(5), NAZAR);
}

TEST(FunctionTest, pop_back)
{
    Danils::Vector<int> vec = {5, 100, 20, 30};
    vec.pop_back();

    ASSERT_EQ(vec.size(), 3);
    ASSERT_EQ(vec.capacity(), 8);

    ASSERT_EQ(vec[0], 5);
    ASSERT_EQ(vec[1], 100);
    ASSERT_EQ(vec[2], 20);
}

TEST_F(TestStudent, pop_back)
{
    students.pop_back();

    ASSERT_EQ(students.size(), 4);
    ASSERT_EQ(students.capacity(), 10);

    ASSERT_EQ(students[0], DANIK);
    ASSERT_EQ(students[1], ANTON);
    ASSERT_EQ(students[2], KATYA);
    ASSERT_EQ(students[3], YARIK);
}

TEST(FunctionTest, pop_front)
{
    Danils::Vector<int> vec = {-5, 100, 20, 30};
    vec.pop_front();

    ASSERT_EQ(vec.size(), 3);
    ASSERT_EQ(vec.capacity(), 8);

    ASSERT_EQ(vec[0], 100);
    ASSERT_EQ(vec[1], 20);
    ASSERT_EQ(vec[2], 30);
}

TEST_F(TestStudent, pop_front)
{
    students.pop_front();

    ASSERT_EQ(students.size(), 4);
    ASSERT_EQ(students.capacity(), 10);

    ASSERT_EQ(students[0], ANTON);
    ASSERT_EQ(students[1], KATYA);
    ASSERT_EQ(students[2], YARIK);
    ASSERT_EQ(students[3], NAZAR);
}

TEST(FunctionTest, insert)
{
    Danils::Vector<char> vec = {'c', 's', 'g', 'o'};
    vec.insert(2, ':');

    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(vec.capacity(), 8);

    ASSERT_EQ(vec[0], 'c');
    ASSERT_EQ(vec[1], 's');
    ASSERT_EQ(vec[2], ':');
    ASSERT_EQ(vec[3], 'g');
    ASSERT_EQ(vec[4], 'o');
}

TEST_F(TestStudent, insert)
{
    Student newStudent(1, 10, "God");
    students.insert(3, newStudent);

    ASSERT_EQ(students.size(), 6);
    ASSERT_EQ(students.capacity(), 10);

    ASSERT_EQ(students[0], DANIK);
    ASSERT_EQ(students[1], ANTON);
    ASSERT_EQ(students[2], KATYA);
    ASSERT_EQ(students[3], newStudent);
    ASSERT_EQ(students[4], YARIK);
    ASSERT_EQ(students[5], NAZAR);
}

TEST_F(TestStudent, insertThrownException)
{
    Student newStudent(1, 10, "God");
    ASSERT_ANY_THROW(students.insert(-1, newStudent));
}

TEST(FunctionTest, erase)
{
    Danils::Vector<char> vec = {'d', 'o', 't', 't', 'a'};
    vec.erase(3);

    ASSERT_EQ(vec.size(), 4);
    ASSERT_EQ(vec.capacity(), 10);

    ASSERT_EQ(vec[0], 'd');
    ASSERT_EQ(vec[1], 'o');
    ASSERT_EQ(vec[2], 't');
    ASSERT_EQ(vec[3], 'a');
}

TEST_F(TestStudent, erase)
{
    students.erase(1);

    ASSERT_EQ(students.size(), 4);
    ASSERT_EQ(students.capacity(), 10);

    ASSERT_EQ(students[0], DANIK);
    ASSERT_EQ(students[1], KATYA);
    ASSERT_EQ(students[2], YARIK);
    ASSERT_EQ(students[3], NAZAR);
}

TEST_F(TestStudent, eraseThrownException)
{
    ASSERT_ANY_THROW(students.erase(-1));
    ASSERT_ANY_THROW(students.erase(static_cast<int>(students.size())));
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
