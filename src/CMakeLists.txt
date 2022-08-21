find_package(Boost 1.53 REQUIRED
    COMPONENTS
        thread
)

find_package(OpenSSL REQUIRED
    COMPONENTS
        Crypto
)

add_library(fileHashLib
    # utils
    utils/DebugMacros.hpp
    utils/ExecutionStats.hpp

    # Abstractions
    abstract/QueueAbstract.hpp
    abstract/BlockReaderAbstract.hpp
    abstract/ReaderBuilderAbstract.hpp
    abstract/BlockProcessorAbstract.hpp
    abstract/ProcessorBuilderAbstract.hpp
    abstract/ResultWriterAbstract.hpp
    abstract/ResultWriterBuilderAbstract.hpp

    # Implementations
    fileReader/FileReaderBuilder.hpp fileReader/FileReaderBuilder.cpp
    fileReader/FileReader.hpp fileReader/FileReader.cpp
    
    hashProcessor/HashProcessor.hpp hashProcessor/HashProcessor.cpp
    hashProcessor/HashProcessorBuilder.hpp hashProcessor/HashProcessorBuilder.cpp
    
    fileWriter/FileWriterBuilder.hpp fileWriter/FileWriterBuilder.cpp
    fileWriter/FileWriter.hpp fileWriter/FileWriter.cpp

    lockFree/LockFreeQueue.hpp lockFree/LockFreeQueue.cpp

    # Application
    blocks/Block.hpp blocks/Block.cpp
    blocks/BlockCache.hpp blocks/BlockCache.cpp

    taskRunner/TaskRunner.hpp taskRunner/TaskRunner.cpp
)

target_include_directories(fileHashLib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(fileHashLib PRIVATE
    Boost::headers
    Boost::thread
    OpenSSL::Crypto
)

add_executable(fileHash
    CLParams.hpp CLParams.cpp
    main.cpp
)

target_link_libraries(fileHash fileHashLib)

install(TARGETS fileHash
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
