#pragma once

#include <list>

#include "ResultWriterAbstract.hpp"

namespace file_hash {
namespace abstract {
class ResultWriterBuilderAbstract {
public:
    virtual ~ResultWriterBuilderAbstract() = default;

    virtual std::string fileName() = 0;
    virtual int resultSize() = 0;
    virtual std::list<ResultWriterAbstract*> getResultWriters(int count = 1) = 0;
};
}
}