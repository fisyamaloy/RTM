#pragma once
#include <deque>
#include <random>

#include "CachingAbstract.hpp"

template <class Key, class value_type>
struct SimpleCache : CachingAbstract<Key, value_type>
{
    SimpleCache() = default;
    SimpleCache(const size_t limit) { setMaxCacheSize(limit); }

    void putItem(const Key& key, const std::shared_ptr<value_type>& valuePtr) override;
    std::shared_ptr<value_type> getItem(const Key& key) const override;
};

template <class Key, class value_type>
void SimpleCache<Key, value_type>::putItem(const Key&                         key,
                                           const std::shared_ptr<value_type>& valuePtr)
{
    std::lock_guard<std::mutex> lg(mut);

    auto mapItemIterator = cacheItems.find(key);
    if (mapItemIterator != cacheItems.end())
    {
        mapItemIterator->second = *valuePtr;
        return;
    }

    if (cacheItems.size() + 1 > maxCacheSize)
    {
        cacheItems.erase(cacheItems.begin());
    }

    cacheItems[key] = *valuePtr;
}

template <class Key, class value_type>
std::shared_ptr<value_type> SimpleCache<Key, value_type>::getItem(const Key& key) const
{
    std::lock_guard<std::mutex> lg(mut);

    const auto mapItemIterator = cacheItems.find(key);
    if (mapItemIterator == cacheItems.cend())
    {
        throw std::range_error("No such key in the cache");
    }

    return std::make_shared<value_type>(mapItemIterator->second);
}
