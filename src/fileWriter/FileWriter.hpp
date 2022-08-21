#pragma once

#include <fstream>

#include "abstract/ResultWriterAbstract.hpp"

namespace file_hash {
namespace fileWriter {
class FileWriter : public abstract::ResultWriterAbstract {
public:
    FileWriter(const std::string &fileName);

    bool writeBlock(blocks::BlockPtr block) override;

private:
    std::ofstream m_fStream;
};
}
}