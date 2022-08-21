#pragma once

#include <fstream>
#include <memory>

#include "abstract/BlockReaderAbstract.hpp"

namespace file_hash {
namespace fileReader {
class FileReader : public abstract::BlockReaderAbstract {
public:
    FileReader(const std::string &fileName, int blockSize, int readFromBlock, int readUntilBlock);

    bool isOpen() override;
    bool readNext(blocks::BlockPtr block) override;
private:

    int m_nextBlock;
    std::ifstream m_fStream;
};
}
}