#pragma once
#include <deque>
#include <random>

#include "CachingCRTP.hpp"

template <class Key, class value_type>
class SimpleCache : public CachingCRTP<SimpleCache<Key, value_type>, Key, value_type>
{
public:
    SimpleCache() = default;
    SimpleCache(const size_t limit) { this->maxCacheSize = limit; }
    ~SimpleCache() = default;

    void putItem(const Key& key, std::shared_ptr<value_type> valuePtr);
    void putItem(const Key&, std::shared_ptr<value_type>&&) = delete;

    std::shared_ptr<value_type> getItem(const Key& key);

    inline void   setMaxCacheSize(const std::size_t limit) { this->maxCacheSize = limit; }
    inline size_t getMaxCacheSize() const { return this->maxCacheSize; }
    inline size_t getCacheSize() const { return this->cacheItems.size(); }
};

template <class Key, class value_type>
void SimpleCache<Key, value_type>::putItem(const Key& key, std::shared_ptr<value_type> valuePtr)
{
    std::lock_guard<std::mutex> lg(this->mut);

    auto mapItemIterator = this->cacheItems.find(key);
    if (mapItemIterator != this->cacheItems.end())
    {
        mapItemIterator->second = valuePtr;
        return;
    }

    if (this->cacheItems.size() >= this->maxCacheSize)
    {
        this->cacheItems.erase(this->cacheItems.begin());
    }

    this->cacheItems[key] = valuePtr;
}

template <class Key, class value_type>
std::shared_ptr<value_type> SimpleCache<Key, value_type>::getItem(const Key& key)
{
    std::lock_guard<std::mutex> lg(this->mut);

    const auto mapItemIterator = this->cacheItems.find(key);
    if (mapItemIterator == this->cacheItems.cend())
    {
        throw std::range_error("No such key in the cache");
    }

    return mapItemIterator->second.lock();
}
