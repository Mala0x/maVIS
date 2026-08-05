#include "FileFuncs.hpp"
#include <fstream>
#include <optional>
#include <print>
#include <variant>

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

    void isFileValid(std::optional<std::fstream>& fileOptional ,std::fstream& maBinFile) {
        if (!fileOptional.has_value()) {
            std::println("Something has gone wrong in the opening of te file! Quitting \n");
            exit(-1);
        } else {
            maBinFile = std::move(fileOptional.value());
        }
    }

    void isFileCorrectFormat(size_t fileExtension) {
        if (fileExtension == std::variant_npos) {
        std::println("Your file is not in the correct format <filename>.mabin is expected! Quitting \n");
        exit(-1);
        }
    }

}