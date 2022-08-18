#pragma once

#include <fstream>

#include "ReaderAbstract.hpp"

class FileReader : public ReaderAbstract {
public:
    FileReader(const std::string &fileName, unsigned blockSize, unsigned blocksCountToRead, int startBlock, OnReadFunctor func);

    char *readNext() override;
private:
    void openFile();

    std::ifstream m_fStream;
};