add_executable(blocksTest
    main.cpp
    BlockCacheTest.cpp
)
target_link_libraries(blocksTest
    ${GTEST_LIBRARIES}
    pthread
    fileHashLib
)

gtest_add_tests(TARGET blocksTest)


