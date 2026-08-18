#pragma once

#include "../../Common/Config.hpp"

#include <fstream>
#include <vector>
#include <cstdint>

class File {
    private:
        // Variables & Constants
        Config &application_config;
        std::fstream ma_bin_file; // This gets the fstream when file is seemingly correct
        // Functions
        void open_file();
        size_t get_file_size();
        void file_in_vector();
    public:
        File(Config &application_config);
        std::vector<uint8_t> vector;
};