#include "HashProcessor.hpp"

#include <iostream>

#include <openssl/md5.h>

using namespace file_hash::hashProcessor;

bool HashProcessor::processBlock(blocks::BlockPtr blockIn, blocks::BlockPtr blockOut)
{
    if (!blockIn || !blockOut)
        return false;

    blockOut->blockNumber = blockIn->blockNumber;

    unsigned char hashBuf[16];
    MD5(reinterpret_cast<const unsigned char*>(blockIn->data), blockIn->blockSize, hashBuf);

    // char buf[sizeof hashBuf * 2 + 1];
    for (int i = 0, j = 0; i < 16; i++, j+=2)
        sprintf(blockOut->data + j, "%02x", hashBuf[i]);
    blockOut->data [blockOut->blockSize * 2] = 0;
    return true;
}