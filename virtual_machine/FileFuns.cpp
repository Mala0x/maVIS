#include "FileFuncs.hpp"
#include <print>

namespace mavis::fileHandler {

    std::optional<std::fstream> openFile(std::string fileName) {

        std::fstream maBinFile;

        try {
            maBinFile.open(fileName, std::ios::in | std::ios::binary);
        } catch(std::exception e) {
            std::println("{}", e.what());
            return {};
        }

        return maBinFile;
    }

    size_t getFileSize(std::fstream& maBinFile) {
        maBinFile.seekg(0, std::ios::end);
        size_t fileSize = maBinFile.tellg();
        maBinFile.seekg(0, std::ios::beg);
        return fileSize;
    }

}