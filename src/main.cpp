#include <iostream>

#include "CLParams.hpp"
#include "FileHashSuperwiser.hpp"

#include "FileReaderBuilder.hpp"

int main(int argc, char **argv)
{
    if (argc < 3) {
        std::cerr << "Not all required parameters set!" << std::endl << std::endl;
        CLParams::showUsage(argv[0]);
        return 0;
    }

    CLParams params;
    for (short i = 1; i < argc; ++i) {
        std::string arg{argv[i]};
        if (arg == "-b" || arg == "--block_size") {
            params.setBlockSize(argv[++i]);
        } else if (arg == "-t" || arg == "--threads") {
            params.setThreadCount(argv[++i]);
        } else {
            if (i == argc - 1) {
                params.setOutputFile(arg);
            } else {
                params.setSourceFile(arg);
            }
        }
    }

    std::cout << "Params are: " << params.getSourceFile() << " "
            << params.getOutputFile() << " "
            << params.getBlockSize() << " "
            << params.getThreadCount() << std::endl;

    if (!params.isValid()) {
        std::cerr << "Params are not valid!" << std::endl;
        CLParams::showUsage(argv[0]);
    } else {
        FileHashSuperwiser sp{FileReaderBuilder{}};
    }

    return 0;
}
