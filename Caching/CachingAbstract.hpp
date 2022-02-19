#pragma once
#include <memory>
#include <mutex>
#include <unordered_map>

template <class Key, class value_type>
class CachingAbstract
{
public:
    inline    void   setMaxCacheSize(const std::size_t limit) { maxCacheSize = limit; }
    constexpr size_t getMaxCacheSize() const { return maxCacheSize; }
    inline    size_t getCacheSize() const { return cacheItems.size(); }

    void         putItem(const Key& key, std::shared_ptr<value_type>&& valuePtr) = delete;
    virtual void putItem(const Key& key, std::shared_ptr<value_type> valuePtr)  = 0;
    
    virtual std::shared_ptr<value_type> getItem(const Key& key) const = 0;
    
    virtual ~CachingAbstract() = default;

protected:
    std::unordered_map<Key, std::weak_ptr<value_type>> cacheItems;
    std::size_t                                        maxCacheSize = 10;
    mutable std::mutex                                 mut;
};
