#include <gtest/gtest.h>

#include "taskRunner/TaskRunner.hpp"

#include "fileReader/FileReaderBuilder.hpp"
#include "hashProcessor/HashProcessorBuilder.hpp"
#include "fileWriter/FileWriterBuilder.hpp"

using namespace file_hash;

TEST(TaskRunnen, NormalCase)
{
    auto readerBuilder = fileReader::FileReaderBuilder{"CTestTestfile.cmake", 512};
    auto processorBuilder = hashProcessor::HashProcessorBuilder{};
    auto writerBuilder = fileWriter::FileWriterBuilder{"taskRunnerTest.txt", processorBuilder.sizeOfResult(), readerBuilder.totalNumberOfBlocks()};

    auto totalBlocks = readerBuilder.totalNumberOfBlocks();
    taskRunner::TaskRunner runner{readerBuilder, processorBuilder, writerBuilder, 1};
    auto stats = runner.run();

    ASSERT_EQ(stats->blocksRead, totalBlocks);
    ASSERT_EQ(stats->blocksWritten, totalBlocks);

    delete stats;
}