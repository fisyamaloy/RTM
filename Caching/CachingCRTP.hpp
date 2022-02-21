#pragma once
#include <memory>
#include <mutex>
#include <unordered_map>

template <class CashingAlgorithm, class Key, class value_type>
class CachingCRTP
{
public:
    inline void   setMaxCacheSize(const std::size_t limit) { self()->setMaxCacheSize() }
    inline size_t getMaxCacheSize() const { return self()->getMaxCacheSize(); }
    inline size_t getCacheSize() const { return self()->getCacheSize(); }

    void putItem(const Key& key, std::shared_ptr<value_type> valuePtr)
    {
        self()->putItem(key, valuePtr);
    }
    void putItem(const Key&, std::shared_ptr<value_type>&&) = delete;

    std::shared_ptr<value_type> getItem(const Key& key) { return self()->getItem(key); }

protected:
    std::unordered_map<Key, std::weak_ptr<value_type>> cacheItems;
    std::size_t                                        maxCacheSize = 10;
    mutable std::mutex                                 mut;

private:
    inline CashingAlgorithm* self() { return static_cast<CashingAlgorithm*>(this); }
};
