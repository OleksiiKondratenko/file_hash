#pragma once

#include <fstream>

#include "abstract/BlockProcessorAbstract.hpp"

namespace file_hash {
namespace hashProcessor {
class HashProcessor : public abstract::BlockProcessorAbstract {
public:
    bool processBlock(blocks::BlockPtr blockIn, blocks::BlockPtr blockOut) override;
};
}
}