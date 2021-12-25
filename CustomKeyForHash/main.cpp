#include <iostream>
#include <unordered_map>

struct CustomKey
{
public:
    int         id;
    size_t      size;

    struct HashFunction
    {
        size_t operator()(const CustomKey& key) const
        {
            size_t idHash   = std::hash<int>()(key.id);
            size_t sizeHash = std::hash<size_t>()(key.size) << 1;

            return idHash ^ sizeHash;
        }
    };

    CustomKey() : id(0), size(0) {}

    CustomKey(const int id, const size_t size)
        : id(id), size(size)
    {
    }

    friend bool operator==(const CustomKey& first, const CustomKey& second)
    {
        return first.id   == second.id && 
               first.size == second.size;
    }
};

int main()
{
    CustomKey first(1, 22);
    CustomKey second(2, 33);
    CustomKey likeFirst(1, 22);

    std::unordered_map<CustomKey, double, CustomKey::HashFunction> map;
    map[first]     = 0.34;
    map[second]    = 0.66;
    map[likeFirst] = 1.1;

    for (const auto& elem : map)
    {
        std::cout << elem.first.id << std::endl;
    }

    return 0;
}
