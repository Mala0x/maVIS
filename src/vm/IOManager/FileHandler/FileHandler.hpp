#pragma once
#include <cstdint>
#include <fstream>
#include <optional>
#include <vector>
#include "../ArgumentHandler/ArgumentHandler.hpp"


namespace mavis {

    class FileHandler {
        private:
            ArgumentHandler argument_handler;
            std::optional<std::fstream> input_file();
            size_t get_file_size();
            bool is_file_valid();
            bool is_file_correct_fomat();
        public:
            std::vector<uint8_t> file_to_vec();
    };

}