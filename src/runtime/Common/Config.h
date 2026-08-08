#pragma once

#include <string>

struct Config {
    bool verbose_mode_set = false;
    bool headless_mode_set = false;
    bool debug_mode_set = false;
    bool logging_to_file_set = false;
    std::string file_to_log_to = "./log.log";
};