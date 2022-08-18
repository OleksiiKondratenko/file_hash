
#include "FileHashSuperwiser.hpp"

#include <iostream>

#include <boost/lockfree/queue.hpp>

FileHashSuperwiser::FileHashSuperwiser(ReaderBuilderAbstract &readerBuilder, uint threads)
    : m_threads(threads),
    m_readerBuilder(readerBuilder)
{
    m_readerBuilder.getReader();
}

void FileHashSuperwiser::constructHash()
{
}