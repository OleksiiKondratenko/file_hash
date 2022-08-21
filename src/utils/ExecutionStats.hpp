#pragma once

#include <chrono>
#include <boost/atomic.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

namespace file_hash {
namespace utils {
struct ExecutionStats {
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;

    boost::atomic_long totalBlocks = 0;
    boost::atomic_long blocksRead = 0;
    boost::atomic_long blocksWritten = 0;

    boost::atomic_llong waitsForReading = 0;
    boost::atomic_llong waitsForProcessing = 0;
    boost::atomic_llong waitsForWriting = 0;
};
}
}