#pragma once

#include <cstddef>
#include <fstream>
#include <optional>
#include <string>

namespace mavis::fileHandler {
    
    std::optional<std::fstream> openFile(std::string fileName);
    size_t getFileSize(std::fstream& maBinFile);

}