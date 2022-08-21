add_executable(taskRunnerTest
    main.cpp
    TaskRunnerTest.cpp
)
target_link_libraries(taskRunnerTest
    ${GTEST_LIBRARIES}
    pthread
    fileHashLib
)

gtest_add_tests(TARGET taskRunnerTest)


