#include <gtest/gtest.h>

#include <list>

#include "blocks/BlockCache.hpp"

using namespace file_hash;

class TestQueue : public abstract::QueueAbstract<blocks::BlockPtr> {
public:
    bool popTry(blocks::BlockPtr &t) override
    {
        t = m_list.front(); m_list.pop_front();
        return true;
    }

    void popWait(blocks::BlockPtr &t) override
    {
        t = m_list.front(); m_list.pop_front();
    }

    void pushWait(blocks::BlockPtr const &t) override
    {
        m_list.push_back(t);
    }

    std::list<blocks::BlockPtr> m_list;
};

TEST(BlockCache, BasicOperations) {
    int cacheSize = 64, blockSize = 5;

    auto testQueue = new TestQueue;
    auto *cache = new blocks::BlockCache{cacheSize, blockSize, testQueue};

    ASSERT_EQ(cacheSize, testQueue->m_list.size());
    for (auto node : testQueue->m_list) {
        ASSERT_EQ(blockSize, node->blockSize);
    }

    auto block = cache->getFreeBlock();
    ASSERT_EQ(testQueue->m_list.size(), cacheSize - 1);
    block->release();
    ASSERT_EQ(testQueue->m_list.size(), cacheSize);
}