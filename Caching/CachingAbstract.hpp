#pragma once
#include <memory>
#include <mutex>
#include <unordered_map>

template <class Key, class value_type>
struct CachingAbstract
{
    virtual void setMaxCacheSize(const std::size_t limit) { maxCacheSize = limit; }

    virtual void putItem(const Key&, const std::shared_ptr<value_type>&) = 0;

    virtual std::shared_ptr<value_type> getItem(const Key& key) const = 0;

    virtual ~CachingAbstract() = default;

protected:
    std::unordered_map<Key, value_type> cacheItems;
    std::size_t                         maxCacheSize = 10;
    mutable std::mutex                  mut;
};
