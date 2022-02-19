#pragma once
#include <deque>
#include <random>

#include "CachingAbstract.hpp"

template <class Key, class value_type>
class SimpleCache : public CachingAbstract<Key, value_type>
{
public:
    SimpleCache() = default;
    SimpleCache(const size_t limit) { this->maxCacheSize = limit; }
    ~SimpleCache() = default;

    void putItem(const Key& key, std::shared_ptr<value_type> valuePtr) override;
    void putItem(const Key& key, std::shared_ptr<value_type>&& valuePtr) = delete;

    std::shared_ptr<value_type> getItem(const Key& key) const override;
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
std::shared_ptr<value_type> SimpleCache<Key, value_type>::getItem(const Key& key) const
{
    std::lock_guard<std::mutex> lg(this->mut);

    const auto mapItemIterator = this->cacheItems.find(key);
    if (mapItemIterator == this->cacheItems.cend())
    {
        throw std::range_error("No such key in the cache");
    }

    return mapItemIterator->second.lock();
}
