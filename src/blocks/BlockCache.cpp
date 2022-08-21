#include "BlockCache.hpp"

using namespace file_hash::blocks;

BlockCache::BlockCache(int cacheSize, int blockSize, abstract::QueueAbstract<BlockPtr> *queue)
    : m_queue(queue)
{
    for (int i = 0; i < cacheSize; ++i) {
        m_queue->pushWait(new Block{ blockSize, *this });
    }
}

BlockCache::~BlockCache()
{
    BlockPtr block = nullptr;
    while (m_queue->popTry(block))
        delete block;
}


BlockPtr BlockCache::getFreeBlock()
{
    BlockPtr p;
    m_queue->popWait(p);
    return p;
}

void BlockCache::releaseBlock(BlockPtr freeBlock)
{
    m_queue->pushWait(freeBlock);
}