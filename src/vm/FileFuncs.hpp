#pragma once

#include <cstddef>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace mavis::fileHandler {
    std::optional<std::fstream> openFile(std::string fileName);
    size_t getFileSize(std::fstream& maBinFile);
    void isFileValid(std::optional<std::fstream>& fileOptional ,std::fstream& maBinFile);
    void isFileCorrectFormat(size_t fileExtension);
    void place_file_in_flash_memory(char* input_file_argv, std::vector<uint8_t> *flash_memory);

}