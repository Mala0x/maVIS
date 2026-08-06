#include "FileFuncs.hpp"
#include <cstdint>
#include <fstream>
#include <optional>
#include <print>
#include <variant>
#include <vector>

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

    void place_file_in_flash_memory(char* input_file_argv, std::vector<uint8_t> *flash_memory) {
        std::string input_file(input_file_argv);

        isFileCorrectFormat(input_file.find(".mabin"));

        auto file_optional = openFile(input_file);

        std::fstream ma_bin_file;

        isFileValid(file_optional, ma_bin_file);

        size_t file_size = getFileSize(ma_bin_file);

        for (size_t i = 0; i < file_size; ++i) {
            flash_memory->emplace_back(ma_bin_file.get());
        }
    }

}