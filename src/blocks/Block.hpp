#pragma once

#include <string>
#include <memory>

namespace file_hash {
namespace blocks {

class BlockCache;

struct Block final {
    Block(int pBlockSize, BlockCache &cache);
    ~Block();

    void release();

    const int blockSize;
    int blockNumber;
    char *data;

private:
    BlockCache &m_cache;
    friend class BlockCache;
};

using BlockPtr = Block*;

}
}