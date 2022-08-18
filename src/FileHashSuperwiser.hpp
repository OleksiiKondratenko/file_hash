#pragma once

#include <string>

#include "ReaderBuilderAbstract.hpp"
// #include "WriterAbstract.hpp"

class FileHashSuperwiser {
    static const uint DEFAULT_THREADS = 1;
public:
    explicit FileHashSuperwiser(ReaderBuilderAbstract &readerBuilder, uint threads = DEFAULT_THREADS);

    void constructHash();

private:
    uint m_threads;
    ReaderBuilderAbstract &m_readerBuilder;
    // WriterAbstract &m_writer;
};