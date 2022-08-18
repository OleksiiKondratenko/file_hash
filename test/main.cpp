#include <iostream>
#include <list>
#include <memory>

#include "FileHashSuperwiserTest.hpp"

int main(int argc, char **argv)
{
    std::list<std::shared_ptr<TestBase>> tests;
    tests.push_back(std::make_shared<FileHashSuperwiserTest>());

    int result = 0;
    for (auto &test : tests) {
        if (!test->run()) {
            std::cerr << "Test failed: " << test->getName() << std::endl;
            result = -1;
        } else {
            std::cout << "Test: " << test->getName() << " passed" << std::endl;
        }
    }

    return result;
}
