#include "FileReader.hpp"

#include <iostream>
#include <cstring>

#include "utils/DebugMacros.hpp"

using namespace file_hash::fileReader;

FileReader::FileReader(const std::string &fileName, int blockSize, int readFromBlock, int readUntilBlock)
    : BlockReaderAbstract(blockSize, readFromBlock, readUntilBlock),
    m_nextBlock(readFromBlock)
{
    m_fStream.open(fileName, std::ios_base::openmode::_S_bin | std::ios_base::openmode::_S_in);

    DEBUG_LOG(std::string{"FileReader: "} + fileName + ", "
        + std::to_string(m_fStream.is_open()) + ", "
        + std::to_string(blockSize) + ", "
        + std::to_string(readFromBlock) + ", "
        + std::to_string(readUntilBlock));
}

bool FileReader::isOpen()
{
    return m_fStream.is_open();
}

bool FileReader::readNext(blocks::BlockPtr block) {
    if (!m_fStream.is_open() || !block) {
        return false;
    }

    auto result = m_fStream.seekg((long long)m_nextBlock * m_blockSize)
        && m_fStream.read(block->data, m_blockSize);

    if (auto charsRead = m_fStream.gcount(); charsRead != m_blockSize) {
        memset(block->data + charsRead, '0', m_blockSize - charsRead);
        m_fStream.close();
    }
    block->blockNumber = m_nextBlock++;
    return true;
}