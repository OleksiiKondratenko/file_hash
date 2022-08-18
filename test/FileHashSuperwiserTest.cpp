#include "FileHashSuperwiserTest.hpp"

#include <sstream>
#include <iostream>
#include <list>

#include "FileHashSuperwiser.hpp"

FileHashSuperwiserTest::FileHashSuperwiserTest()
    : TestBase("FileHashSuperwiserTest")
{}

bool FileHashSuperwiserTest::run()
{
    // class TestReader : public ReaderAbstract {
    // public:
    //     std::basic_istream<char> *getNext() override {
    //         static uint counter = 0;

    //         if (counter > 10)
    //             return nullptr;
    //         ++counter;

    //         std::stringstream *str = new std::stringstream;
    //         str->str(std::string{"StreamStream"});
    //         return str;
    //     }
    // } testReader;

    // class TestWriter : public WriterAbstract {
    // public:
    //     ~TestWriter() {
    //         for (auto *c : resultHash) {
    //             delete c;
    //         }
    //     }

    //     void putNext(const char *data) override {
    //         resultHash.push_back(data);
    //     }

    //     std::list<const char*> resultHash;
    // } testWriter;

    // FileHashSuperwiser testSup{testReader, testWriter};
    // testSup.constructHash();

    // bool result = !testWriter.resultHash.empty();

    // return result;
    return false;
}
