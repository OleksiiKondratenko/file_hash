#include "HashProcessorBuilder.hpp"

#include <openssl/md5.h>
#include "HashProcessor.hpp"

using namespace file_hash::abstract;
using namespace file_hash::hashProcessor;

int HashProcessorBuilder::sizeOfResult()
{
    return MD5_DIGEST_LENGTH * 2;
}

std::list<BlockProcessorAbstract*> HashProcessorBuilder::getProcessors(int count)
{
    std::list<BlockProcessorAbstract*> list;
    for (int i = 0; i < count; ++i) {
        list.push_back(new HashProcessor);
    }
    return list;
}