#pragma once

#include "blocks/Block.hpp"
#include "utils/Defs.hpp"

namespace file_hash {
namespace abstract {
class BlockReaderAbstract {
public:
    NO_COPY_MOVE(BlockReaderAbstract)

    virtual ~BlockReaderAbstract() = default;

    virtual bool isOpen() = 0;
    virtual bool readNext(blocks::BlockPtr block) = 0;
protected:
    BlockReaderAbstract(int blockSize, int readFromBlock, int readUntilBlock)
        : m_blockSize(blockSize),
        m_readFromBlock(readFromBlock),
        m_readUntilBlock(readUntilBlock)
    {}

    const int m_blockSize;
    const int m_readFromBlock;
    const int m_readUntilBlock;
};
}
}