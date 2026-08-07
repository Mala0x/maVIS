#include "FileFuncs.hpp"
#include <cstdint>
#include <fstream>
#include <optional>
#include <print>
#include <variant>
#include <vector>

namespace mavis::fileHandler {

    std::optional<std::fstream> open_file(std::string file_name) {

        std::fstream ma_bin_file;

        try {
            ma_bin_file.open(file_name, std::ios::in | std::ios::binary);
        } catch(std::exception e) {
            std::println("{}", e.what());
            return {};
        }

        return ma_bin_file;
    }

    size_t get_file_size(std::fstream& ma_bin_file) {
        ma_bin_file.seekg(0, std::ios::end);
        size_t file_size = ma_bin_file.tellg();
        ma_bin_file.seekg(0, std::ios::beg);
        return file_size;
    }

    void is_file_valid(std::optional<std::fstream>& file_optional ,std::fstream& ma_bin_file) {
        if (!file_optional.has_value()) {
            std::println("Something has gone wrong in the opening of te file! Quitting \n");
            exit(-1);
        } else {
            ma_bin_file = std::move(file_optional.value());
        }
    }

    void is_file_correct_format(size_t file_extension) {
        if (file_extension == std::variant_npos) {
        std::println("Your file is not in the correct format <file_name>.mabin is expected! Quitting \n");
        exit(-1);
        }
    }

    void place_file_in_flash_memory(char* input_file_argv, std::vector<uint8_t> *flash_memory) {
        std::string input_file(input_file_argv);

        is_file_correct_format(input_file.find(".mabin"));

        auto file_optional = open_file(input_file);

        std::fstream ma_bin_file;

        is_file_valid(file_optional, ma_bin_file);

        size_t file_size = get_file_size(ma_bin_file);

        for (size_t i = 0; i < file_size; ++i) {
            flash_memory->emplace_back(ma_bin_file.get());
        }
    }

}