#pragma once

#include <string>

#include "abstract/ProcessorBuilderAbstract.hpp"

namespace file_hash {
namespace hashProcessor {
class HashProcessorBuilder : public abstract::ProcessorBuilderAbstract
{
public:
    int sizeOfResult() override;
    std::list<abstract::BlockProcessorAbstract*> getProcessors(int count = 1) override;
};
}
}