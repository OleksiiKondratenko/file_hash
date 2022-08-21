#pragma once

#include "utils/Defs.hpp"

#include "blocks/Block.hpp"

namespace file_hash {
namespace abstract {
class BlockProcessorAbstract {
public:
    NO_COPY_MOVE(BlockProcessorAbstract)

    explicit BlockProcessorAbstract() = default;
    virtual ~BlockProcessorAbstract() = default;

    virtual bool processBlock(blocks::BlockPtr blockIn, blocks::BlockPtr blockOut) = 0;
};
}
}