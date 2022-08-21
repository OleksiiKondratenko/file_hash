#pragma once

#include <string>

#define KByte 1024
#define MByte 1024*1024

namespace file_hash {
class CLParams {   
public:
    static constexpr int DEFAULT_BLOCK_SIZE = 1 * MByte;

    static void showUsage(char *name);

    bool isValid() const;

    void setSourceFile(const std::string &val);
    void setOutputFile(const std::string &val);
    void setBlockSize(const std::string &val);
    void setThreadCount(const std::string &val);

    const std::string &getSourceFile() const;
    const std::string &getOutputFile() const;
    int getBlockSize() const;
    int getThreadCount() const;

private:
    std::string m_sourceFile;
    std::string m_outputFile;
    int m_blockSize = DEFAULT_BLOCK_SIZE;
    int m_threadCount = 0;
};

}