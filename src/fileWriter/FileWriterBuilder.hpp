#pragma once

#include <string>

#include "abstract/ResultWriterBuilderAbstract.hpp"

namespace file_hash {
namespace fileWriter {
class FileWriterBuilder : public abstract::ResultWriterBuilderAbstract
{
public:
    FileWriterBuilder(const std::string &fileName, int resultSize, int totalBlocks);

    std::string fileName() override;
    int resultSize() override;
    std::list<abstract::ResultWriterAbstract*> getResultWriters(int count) override;

private:
    const int m_resultSize;
    const std::string m_fileName;
};
}
}
