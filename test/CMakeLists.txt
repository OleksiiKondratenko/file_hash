add_executable(testRunner
    main.cpp
    FileHashSuperwiserTest.hpp FileHashSuperwiserTest.cpp
)

target_link_libraries(testRunner fileHashLib)
