find_package(GTest QUIET)

if(GTest_FOUND)
    enable_testing()

    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(blocks)
    add_subdirectory(taskRunner)
else()
    message(STATUS "GTest not found, tests will not be included.")
endif()
