#include "Block.hpp"

#include "BlockCache.hpp"

using namespace file_hash::blocks;

Block::Block(int pBlockSize, BlockCache &cache)
    : blockSize(pBlockSize),
    m_cache(cache)
{
    data = new char[blockSize];
}

Block::~Block() { delete[] data; }

void Block::release()
{
    m_cache.releaseBlock(this);
}