#pragma once

#include "abstract/QueueAbstract.hpp"

#include "Block.hpp"

namespace file_hash {
namespace blocks {

class BlockCache {
public:
    BlockCache(int cacheSize, int blockSize, abstract::QueueAbstract<BlockPtr> *queue);
    ~BlockCache();

    BlockPtr getFreeBlock();

private:
    void releaseBlock(BlockPtr freeBlock);

    std::unique_ptr<abstract::QueueAbstract<BlockPtr>> m_queue;
    
    friend class Block;
};

}
}