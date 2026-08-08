#include "Arguments.hpp"

#include "print"

Arguments::Arguments(int argc, char* argv[], Config &application_config) : application_config(application_config) {

    std::println("arg count: {}", argc);

    for (int i = 0; i < argc; i++) {
        std::println("Argument: {}", argv[i]);
        this->parsed_arguments.emplace_back(std::string(argv[i])); // Converts from char* to std::string for safety and QOL features
    }

    for (std::string items : this->parsed_arguments) {
        if (items == "--v") {
            this->application_config.verbose_mode_set = true;
        }
    }

    std::println("testing: {}", this->application_config.verbose_mode_set);

}