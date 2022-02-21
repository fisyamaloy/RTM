#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "SimpleCache.hpp"

TEST(SimpleCache, getMaxCacheSize)
{
    auto simpleCaching = std::make_unique<SimpleCache<char, int>>(4);
    ASSERT_EQ(simpleCaching->getMaxCacheSize(), 4);

    simpleCaching->setMaxCacheSize(21);
    ASSERT_EQ(simpleCaching->getMaxCacheSize(), 21);
}

TEST(SimpleCache, putItem)
{
    auto simpleCaching = std::make_unique<SimpleCache<char, int>>(15);

    auto sp_1 = std::make_shared<int>(1);
    auto sp_2 = std::make_shared<int>(1);
    auto sp_3 = std::make_shared<int>(2);
    auto sp_4 = std::make_shared<int>(3);
    auto sp_5 = std::make_shared<int>(5);

    simpleCaching->putItem('a', sp_1);
    simpleCaching->putItem('b', sp_2);
    simpleCaching->putItem('c', sp_3);
    simpleCaching->putItem('d', sp_4);
    simpleCaching->putItem('d', sp_5);
    ASSERT_EQ(simpleCaching->getCacheSize(), 4);

    simpleCaching->putItem('e', sp_5);
    ASSERT_EQ(simpleCaching->getCacheSize(), 5);

    simpleCaching->putItem('f', sp_5);
    ASSERT_EQ(simpleCaching->getCacheSize(), 6);
}

TEST(SimpleCache, getItem)
{
    auto simpleCaching = std::make_unique<SimpleCache<char, int>>(4);

    auto sp_1 = std::make_shared<int>(1);
    auto sp_2 = std::make_shared<int>(1);
    auto sp_3 = std::make_shared<int>(2);

    simpleCaching->putItem('a', sp_1);
    simpleCaching->putItem('b', sp_2);
    simpleCaching->putItem('c', sp_3);

    auto sp_1_1 = simpleCaching->getItem('a');
    ASSERT_TRUE(sp_1 == sp_1_1);

    auto sp_2_2 = simpleCaching->getItem('b');
    ASSERT_TRUE(sp_2 == sp_2_2);

    EXPECT_THROW(simpleCaching->getItem('Z'), std::range_error);
}

TEST(SimpleCashing, putItemUsingCRTPObject)
{
    auto simpleCaching = std::make_unique<CachingCRTP<SimpleCache<char, int>, char, int>>();

    auto                   sp_1 = std::make_shared<int>(1);
    auto                   sp_2 = std::make_shared<int>(1);
    auto                   sp_3 = std::make_shared<int>(2);

    simpleCaching->putItem('a', sp_1);
    simpleCaching->putItem('b', sp_2);
    simpleCaching->putItem('c', sp_3);

    auto sp_1_1 = simpleCaching->getItem('a');
    ASSERT_TRUE(sp_1 == sp_1_1);
}

struct User
{
    int         id;
    std::string name;

    friend bool operator==(const User& left, const User& right)
    {
        return left.id == right.id && left.name == right.name;
    }

    User& operator=(const User& user)
    {
        this->id   = user.id;
        this->name = user.name;
        return *this;
    }

    struct HashFunction
    {
        size_t operator()(const User& key) const
        {
            size_t idHash   = std::hash<int>()(key.id);
            size_t sizeHash = std::hash<std::string>()(key.name) << 1;

            return idHash ^ sizeHash;
        }
    };
};

namespace std
{
    template <>
    struct hash<User>
    {
        std::size_t operator()(const User& key) const
        {
            return ((std::hash<std::string>()(key.name) ^ (std::hash<int>()(key.id) << 1)));
        }
    };

}  // namespace std

TEST(SimpleCache_CustomType, putItemWithCustomValue)
{
    User user_1{1, "Danil"}, user_2{2, "Katya"}, user_3{3, "asfs"}, user_4{4, "fgsdfsdfg"};
    auto sp_1 = std::make_shared<User>(user_1);
    auto sp_2 = std::make_shared<User>(user_2);
    auto sp_3 = std::make_shared<User>(user_3);
    auto sp_4 = std::make_shared<User>(user_4);

    auto simpleCaching = std::make_unique<SimpleCache<int, User>>(3);
    simpleCaching->putItem(1, sp_1);
    simpleCaching->putItem(2, sp_2);
    simpleCaching->putItem(3, sp_3);
    ASSERT_EQ(simpleCaching->getCacheSize(), 3);

    simpleCaching->putItem(4, sp_4);
    ASSERT_EQ(simpleCaching->getCacheSize(), 3);
}

TEST(SimpleCache_CustomType, putItemWithCustomKey)
{
    User user_1{1, "Danil"}, user_2{2, "Katya"}, user_3{3, "asfs"}, user_4{4, "fgsdfsdfg"};
    auto simpleCaching = std::make_unique<SimpleCache<User, int>>(3);

    auto sp_1 = std::make_shared<int>(1);
    auto sp_2 = std::make_shared<int>(1);
    auto sp_3 = std::make_shared<int>(2);

    simpleCaching->putItem(user_1, sp_1);
    simpleCaching->putItem(user_2, sp_2);
    simpleCaching->putItem(user_3, sp_3);
    simpleCaching->putItem(user_4, sp_3);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
