#pragma once

#include <list>

#include "BlockProcessorAbstract.hpp"

namespace file_hash {
namespace abstract {
class ProcessorBuilderAbstract {
public:
    explicit ProcessorBuilderAbstract() = default;
    virtual ~ProcessorBuilderAbstract() = default;

    virtual int sizeOfResult() = 0;
    virtual std::list<BlockProcessorAbstract*> getProcessors(int count = 1) = 0;
};

}
}