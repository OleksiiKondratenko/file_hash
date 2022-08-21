#pragma once

#include <list>

#include "BlockReaderAbstract.hpp"

namespace file_hash {
namespace abstract {
class ReaderBuilderAbstract {
public:
    virtual ~ReaderBuilderAbstract() = default;

    virtual std::string fileName() = 0;
    virtual int blockSize() = 0;
    virtual int totalNumberOfBlocks() = 0;
    virtual std::list<BlockReaderAbstract*> getReaders(int count = 1) = 0;
};
}
}