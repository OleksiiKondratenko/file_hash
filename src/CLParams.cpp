#include "CLParams.hpp"

#include <iostream>

using namespace file_hash;

void CLParams::showUsage(char *name)
{
    std::cerr << "Usage: " << name << " <option(s)> source_file output_file" << std::endl
        << "Options:" << std::endl
        << "\t-b,--block_size\tdefines block size (b = Byte, k - KByte, m - MByte), default is 1M" << std::endl
        << "\t-t,--threads\tdefines amount of parallel threads for processors, default: either number of cores or 1 if not detectable."
        << std::endl;
}

bool CLParams::isValid() const
{
    return !m_outputFile.empty() && !m_sourceFile.empty() && m_blockSize >= 512 && m_blockSize <= 10485760 && getThreadCount() > 0;
}

void CLParams::setSourceFile(const std::string &val)
{
    m_sourceFile = val;
}

void CLParams::setOutputFile(const std::string &val)
{
    m_outputFile = val;
}

void CLParams::setBlockSize(const std::string &val)
{
    m_blockSize = std::stoi(val.substr(0, val.size()));
    switch (val.back()) {
    case 'k':
    case 'K':
        m_blockSize *= KByte;
        break;
    case 'm':
    case 'M':
        m_blockSize *= MByte;
        break;
    }
}

void CLParams::setThreadCount(const std::string &val)
{
    m_threadCount = std::stoi(val);
}

const std::string &CLParams::getSourceFile() const
{
    return m_sourceFile;
}

const std::string &CLParams::getOutputFile() const
{
    return m_outputFile;
}

int CLParams::getBlockSize() const
{
    return m_blockSize;
}

int CLParams::getThreadCount() const
{
    return m_threadCount == 0 ? 1 : m_threadCount;
}