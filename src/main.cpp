#include <iostream>

#include "CLParams.hpp"
#include "taskRunner/TaskRunner.hpp"

#include "fileReader/FileReaderBuilder.hpp"
#include "hashProcessor/HashProcessorBuilder.hpp"
#include "fileWriter/FileWriterBuilder.hpp"

using namespace file_hash;

int main(int argc, char **argv)
{
    if (argc < 3) {
        std::cerr << "Not all required parameters set!" << std::endl << std::endl;
        CLParams::showUsage(argv[0]);
        return 0;
    }

    CLParams params;
    for (short i = 1; i < argc; ++i) {
        std::string arg{argv[i]};
        if (arg == "-b" || arg == "--block_size") {
            params.setBlockSize(argv[++i]);
        } else if (arg == "-t" || arg == "--threads") {
            params.setThreadCount(argv[++i]);
        } else {
            if (i == argc - 1) {
                params.setOutputFile(arg);
            } else {
                params.setSourceFile(arg);
            }
        }
    }

    std::cout << "Params are: " << params.getSourceFile() << " "
            << params.getOutputFile() << " "
            << params.getBlockSize() << " "
            << params.getThreadCount() << std::endl;

    if (!params.isValid()) {
        std::cerr << "Params are not valid!" << std::endl;
        CLParams::showUsage(argv[0]);
    } else {
        auto readerBuilder = fileReader::FileReaderBuilder{params.getSourceFile(), params.getBlockSize()};
        auto processorBuilder = hashProcessor::HashProcessorBuilder{};
        auto writerBuilder = fileWriter::FileWriterBuilder{params.getOutputFile(), processorBuilder.sizeOfResult(), readerBuilder.totalNumberOfBlocks()};

        std::cout << "Start processing: " << std::endl << std::endl;
        std::cout << "Input File: " << readerBuilder.fileName() << ", total blocks: " << readerBuilder.totalNumberOfBlocks() << std::endl << std::endl;
        std::cout << "Output File: " << readerBuilder.fileName() << std::endl << std::endl;

        taskRunner::TaskRunner runner{readerBuilder, processorBuilder, writerBuilder, params.getThreadCount()};
        auto stats = runner.run();

        std::cout << std::endl << "Processing finished: " << std::endl << std::endl;
        if (stats) {
            std::cout << "Duration: " << duration<double, std::milli>(stats->endTime - stats->startTime).count() << " msec." << std::endl << std::endl;
            std::cout << "Blocks: " << std::endl
                << "Total blocks: " << stats->totalBlocks << std::endl
                << "Blocks read: " << stats->blocksRead << std::endl
                << "Blocks written: " << stats->blocksWritten << std::endl << std::endl;
            std::cout << "Empty spins contention: " << std::endl
                << " waits for reading: " << stats->waitsForReading << std::endl
                << " waits for processing: " << stats->waitsForProcessing << std::endl
                << " waits for writing: " << stats->waitsForWriting << std::endl
            ;
        } else {
            std::cout << "Execution failed!";
        }

        delete stats;
    }

    return 0;
}
