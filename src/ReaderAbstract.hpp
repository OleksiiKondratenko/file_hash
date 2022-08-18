#pragma once

class ReaderAbstract {
public:
    using OnReadFunctor = void(*)(char *);

    ReaderAbstract(unsigned blockSize, unsigned blocksCountToRead, int startBlock, OnReadFunctor func)
        : m_blockSize(blockSize),
        m_blocksCountToRead(blocksCountToRead),
        m_startBlock(startBlock)
    {}

    virtual ~ReaderAbstract() = default;

    virtual char *readNext() = 0;

    void operator()() {
        while (auto bytes = readNext()) {
            m_func(bytes);
        }
    }

protected:

    const unsigned m_blockSize;
    const unsigned m_blocksCountToRead;
    const int m_startBlock;

    OnReadFunctor m_func;
};