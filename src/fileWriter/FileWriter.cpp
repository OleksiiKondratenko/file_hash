#include "FileWriter.hpp"

#include <cstring>

#include "utils/DebugMacros.hpp"

using namespace file_hash::fileWriter;

FileWriter::FileWriter(const std::string &fileName)
{
    m_fStream.open(fileName);
}

bool FileWriter::writeBlock(blocks::BlockPtr block)
{
    if (!block)
        return false;

    auto result = m_fStream.seekp((long long)block->blockNumber * (block->blockSize + 1))
        && m_fStream.write(block->data, block->blockSize);
    
    if (!result) {
        DEBUG_LOG(std::string{"FileWriter: write failed! "} + std::to_string(m_fStream.failbit));
        return false;
    }
    m_fStream << std::endl;
    return true;
}
