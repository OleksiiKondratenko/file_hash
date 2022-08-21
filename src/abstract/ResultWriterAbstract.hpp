#pragma once

#include "blocks/Block.hpp"
#include "utils/Defs.hpp"

namespace file_hash {
namespace abstract {
class ResultWriterAbstract {
public:
    NO_COPY_MOVE(ResultWriterAbstract)

    explicit ResultWriterAbstract() = default;
    virtual ~ResultWriterAbstract() = default;

    virtual bool writeBlock(blocks::BlockPtr block) = 0;
};
}
}