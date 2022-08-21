#include "FileReaderBuilder.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>

#include "FileReader.hpp"

using namespace file_hash;
using namespace file_hash::fileReader;

FileReaderBuilder::FileReaderBuilder(const std::string &fileName, int blockSize)
    : m_blockSize(blockSize),
    m_fileName(fileName)
{
    auto fileSize = std::filesystem::file_size(fileName);
    m_totalBlocks = std::ceil(double(fileSize) / blockSize);
}

std::string FileReaderBuilder::fileName()
{
    return m_fileName;
}

int FileReaderBuilder::blockSize()
{
    return m_blockSize;
}

int FileReaderBuilder::totalNumberOfBlocks()
{
    return m_totalBlocks;
}

std::list<abstract::BlockReaderAbstract*> FileReaderBuilder::getReaders(int count)
{
    std::list<abstract::BlockReaderAbstract*> list;

    int batchSize = std::ceil(double(m_totalBlocks) / count);
    for (; m_totalBlocks > 0; m_totalBlocks -= batchSize) {
        int firstBlock = batchSize * list.size();
        list.push_back(new FileReader{m_fileName, m_blockSize, firstBlock, firstBlock + std::min(batchSize, m_totalBlocks)});
    }

    return list;
}