#pragma once

#include <string>

#include "abstract/ReaderBuilderAbstract.hpp"
#include "abstract/ProcessorBuilderAbstract.hpp"
#include "abstract/ResultWriterBuilderAbstract.hpp"

#include "utils/ExecutionStats.hpp"

namespace file_hash {
namespace taskRunner {

class TaskRunner {
    static const int DEFAULT_THREADS = 1;
public:
    explicit TaskRunner(abstract::ReaderBuilderAbstract &readerBuilder, abstract::ProcessorBuilderAbstract &processorBuilder,
        abstract::ResultWriterBuilderAbstract &writerBuilder, int threads = DEFAULT_THREADS);

    utils::ExecutionStats *run();

private:
    int m_threads;
    abstract::ReaderBuilderAbstract &m_readerBuilder;
    abstract::ProcessorBuilderAbstract &m_processorBuilder;
    abstract::ResultWriterBuilderAbstract &m_writerBuilder;
};

}
}