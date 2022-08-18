#pragma once

#include <string>

class CLParams {    
public:
    static void showUsage(char *name);

    bool isValid() const;

    void setSourceFile(const std::string &val);
    void setOutputFile(const std::string &val);
    void setBlockSize(const std::string &val);
    void setThreadCount(const std::string &val);

    const std::string &getSourceFile() const;
    const std::string &getOutputFile() const;
    uint getBlockSize() const;
    uint getThreadCount() const;

private:
    std::string m_sourceFile;
    std::string m_outputFile;
    uint m_blockSize = 512;
    uint m_threadCount = 1;
};