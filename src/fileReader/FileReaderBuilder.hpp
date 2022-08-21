#pragma once

#include <string>

#include "abstract/ReaderBuilderAbstract.hpp"

namespace file_hash {
namespace fileReader {
class FileReaderBuilder : public abstract::ReaderBuilderAbstract
{
public:
    FileReaderBuilder(const std::string &fileName, int blockSize);

    std::string fileName() override;
    int blockSize() override;
    int totalNumberOfBlocks() override;
    std::list<abstract::BlockReaderAbstract*> getReaders(int count) override;

private:
    int m_totalBlocks;
    const int m_blockSize;
    const std::string m_fileName;
};
}
}