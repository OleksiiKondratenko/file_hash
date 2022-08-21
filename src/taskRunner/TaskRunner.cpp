
#include "TaskRunner.hpp"

#include <iostream>

#include <boost/atomic.hpp>
#include <boost/thread/thread.hpp>

#include "utils/DebugMacros.hpp"

#include "blocks/BlockCache.hpp"
#include "lockFree/LockFreeQueue.hpp"

using namespace file_hash::lockFree;
using namespace file_hash::blocks;
using namespace file_hash::taskRunner;
using namespace file_hash::abstract;
using namespace file_hash::utils;

constexpr auto cacheSize = 64;

void map(BlockReaderAbstract *reader, BlockCache *mapBlockCache, LockFreeQueue *mappedBlocksQ, ExecutionStats *stats) {
    static boost::atomic_int readerCount = 0;

    auto readerNumber = ++readerCount;

    DEBUG_LOG(std::string("Reader start: ") + std::to_string(readerNumber));

    while (reader->isOpen()) {
        auto block = mapBlockCache->getFreeBlock();
        
        if (!reader->readNext(block))
            break;
        ++stats->blocksRead;
        mappedBlocksQ->pushWait(block);
    }
};

void reduce(BlockProcessorAbstract *processor, BlockCache *reduceBlockCache, LockFreeQueue *mappedBlocksQ, LockFreeQueue *reducedBlocks, ExecutionStats *stats)
{
    static boost::atomic_int processCount = 0;
    auto processNumber = ++processCount;
    boost::atomic_bool interrupted = false;

    DEBUG_LOG(std::string("Processor start: ") + std::to_string(processNumber));

    auto processBlocks = [&](){
        bool isEmpty = true;
        BlockPtr blockIn;
        while (mappedBlocksQ->popTry(blockIn)) {
            isEmpty = false;

            auto blockOut = reduceBlockCache->getFreeBlock();

            if (!processor->processBlock(blockIn, blockOut)) {
                interrupted = true;
                break;
            }
            reducedBlocks->pushWait(blockOut);

            blockIn->release();
        }

        if (isEmpty) {
            ++stats->waitsForReading;
        }
    };

    while (stats->blocksWritten != stats->totalBlocks && !interrupted) {
        processBlocks();
    }
    processBlocks();
};

void writeResult(ResultWriterAbstract *writer, LockFreeQueue *reducedBlocks, ExecutionStats *stats){
    static boost::atomic_int writerCount = 0;
    auto writerNumber = ++writerCount;
    boost::atomic_bool interrupted = false;

    DEBUG_LOG(std::string("Writer start: ") + std::to_string(writerNumber));

    auto writeBlocks = [&](){
        bool isEmpty = true;
        BlockPtr block;
        while (reducedBlocks->popTry(block)) {
            isEmpty = false;

            if (!writer->writeBlock(block)) {
                interrupted = true;
                break;
            }
            ++stats->blocksWritten;
            block->release();
        }

        if (isEmpty) {
            ++stats->waitsForProcessing;
        }
    };

    while (stats->blocksWritten != stats->totalBlocks && !interrupted) {
        writeBlocks();
    }
    
    writeBlocks();
};

TaskRunner::TaskRunner(ReaderBuilderAbstract &readerBuilder, ProcessorBuilderAbstract &processorBuilder,
    ResultWriterBuilderAbstract &writerBuilder, int threads)
    : m_threads(threads),
    m_readerBuilder(readerBuilder),
    m_processorBuilder(processorBuilder),
    m_writerBuilder(writerBuilder)
{
}

ExecutionStats *TaskRunner::run()
{
    ExecutionStats *stats = new ExecutionStats;
    stats->totalBlocks = m_readerBuilder.totalNumberOfBlocks();

    BlockCache mapBlockCache{cacheSize, m_readerBuilder.blockSize(), new LockFreeQueue},
        reduceBlockCache{cacheSize, m_writerBuilder.resultSize(), new LockFreeQueue};
    LockFreeQueue mappedBlocksQ, reducedBlocks;

    boost::thread_group readerThreads, processorThreads, writerThreads;

    stats->startTime = high_resolution_clock::now();
    {
        auto readerList = m_readerBuilder.getReaders(1);
        auto processorList = m_processorBuilder.getProcessors(m_threads);
        auto writerList = m_writerBuilder.getResultWriters(1);

        for (auto *reader : readerList) {
            readerThreads.add_thread(new boost::thread(map, reader, &mapBlockCache, &mappedBlocksQ, stats));
        }
        for (auto *processor : processorList) {
            processorThreads.add_thread(new boost::thread(reduce, processor, &reduceBlockCache, &mappedBlocksQ, &reducedBlocks, stats));
        }
        for (auto *writer : writerList) {
            writerThreads.add_thread(new boost::thread(writeResult, writer, &reducedBlocks, stats));
        }

        auto printProgress = [stats](){
            auto secsPassed = duration<double, std::milli>(high_resolution_clock::now() - stats->startTime).count() / 1000;
            auto avg = (double)stats->blocksWritten / secsPassed;
            std::cout << "\r" << "Processing blocks: " << stats->blocksWritten << " written, "
                << secsPassed << " msec. passed, "
                << (double)stats->blocksWritten / stats->totalBlocks * 100 << " \% done, "
                << "avg. " << avg
                << " est.: " << ((double)stats->totalBlocks - stats->blocksWritten) / avg / 60 << " min.               "
                << std::flush;
        };

        while (stats->blocksWritten < stats->totalBlocks) {
            printProgress();
            boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        }
        printProgress();

        readerThreads.join_all();
        processorThreads.join_all();
        writerThreads.join_all();

        for (auto ptr : readerList) delete ptr;
        for (auto ptr : processorList) delete ptr;
        for (auto ptr : writerList) delete ptr;
    }

    stats->endTime = high_resolution_clock::now();
    return stats;
}
