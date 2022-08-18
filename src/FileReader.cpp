#include "FileReader.hpp"

FileReader::FileReader(const std::string &fileName, unsigned blockSize, unsigned blocksCountToRead, int startBlock, OnReadFunctor func)
    : ReaderAbstract(blockSize, blocksCountToRead, startBlock, func)
{
    m_fStream.open(fileName);
}

char *FileReader::readNext() {
    if (!m_fStream.is_open()) {
        return nullptr;
    }

    char *buf = new char[m_blockSize];
    m_fStream.read(buf, m_blockSize);

    return buf;
}