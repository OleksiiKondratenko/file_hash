find_package(Boost 1.53 REQUIRED
    COMPONENTS
        thread
)

add_library(fileHashLib
    # Abstractions
    ReaderAbstract.hpp
    BuilderAbstract.hpp
    ReaderBuilderAbstract.hpp

    # Implementations
    FileReaderBuilder.hpp
    FileReader.hpp FileReader.cpp

    # Application
    FileHashSuperwiser.hpp FileHashSuperwiser.cpp
)

target_include_directories(fileHashLib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(fileHashLib PRIVATE Boost::headers)

add_executable(fileHash
    CLParams.hpp CLParams.cpp
    main.cpp
)

target_link_libraries(fileHash fileHashLib)

install(TARGETS fileHash
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
