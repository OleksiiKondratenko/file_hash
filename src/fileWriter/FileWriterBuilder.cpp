#include "FileWriterBuilder.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>

#include "FileWriter.hpp"

using namespace file_hash::abstract;
using namespace file_hash::fileWriter;

FileWriterBuilder::FileWriterBuilder(const std::string &fileName, int resultSize, int totalBlocks)
    : m_fileName(fileName),
    m_resultSize(resultSize)
{
    std::fstream outputFile{fileName, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_trunc};
}

std::string FileWriterBuilder::fileName()
{
    return m_fileName;
}

int FileWriterBuilder::resultSize()
{
    return m_resultSize;
}

std::list<ResultWriterAbstract*> FileWriterBuilder::getResultWriters(int count)
{
    std::list<ResultWriterAbstract*> list;

    for (int i = 0; i < count; ++i) {
        list.push_back(new FileWriter{m_fileName});
    }

    return list;
}
