#include "CLParams.hpp"

#include <iostream>

void CLParams::showUsage(char *name)
{
    std::cerr << "Usage: " << name << " <option(s)> source_file output_file" << std::endl
        << "Options:" << std::endl
        << "\t-b,--block_size\tdefines block size (b = Byte, k - KByte, m - MByte), default is 1M" << std::endl
        << "\t-t,--threads\tdefines amout of parallel threads, default: either number of cores or 1 if not detectable."
        << std::endl;
}

bool CLParams::isValid() const
{
    return !m_outputFile.empty() && !m_sourceFile.empty() && m_blockSize >= 512 && m_blockSize <= 10485760 && m_threadCount > 0;
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
    uint multiplier = 0;
    switch (val.back()) {
    case 'b':
    case 'B':
        multiplier = 1;
        break;
    case 'k':
    case 'K':
        multiplier = 1024;
        break;
    case 'm':
    case 'M':
        multiplier = 1024 * 1024;
        break;
    }
    m_blockSize = std::stoi(val.substr(0, val.size())) * multiplier;
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

uint CLParams::getBlockSize() const
{
    return m_blockSize;
}

uint CLParams::getThreadCount() const
{
    return m_threadCount;
}