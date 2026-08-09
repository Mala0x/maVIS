#include "Arguments.hpp"

#include "print"

Arguments::Arguments(int argc, char* argv[], Config &application_config) : application_config(application_config) {
    std::println("arg count: {}", argc);

    for (int i = 0; i < argc; i++) {
        std::println("Argument: {}", argv[i]);
        this->parsed_arguments.emplace_back(std::string(argv[i])); // Converts from char* to std::string for safety
    }

    this->parse_arguments();

}

void Arguments::parse_arguments() {

    for (size_t i = 0; i < this->parsed_arguments.size(); i++) {
        
        if (this->parsed_arguments[i] == "--v") { // Might go and make smaller functions for each argument
            std::println("Verbose mode called!");
            this->application_config.verbose_mode_set = true;
        } else if (this->parsed_arguments[i] == "--headless") {
            std::println("Headless mode is called!");
            this->application_config.headless_mode_set = true;
        } else if (this->parsed_arguments[i] == "--debug") {
            std::println("Debug mode wanted!");
            this->application_config.debug_mode_set = true;
        } else if (this->parsed_arguments[i] == "--log") {
            std::println("Logging to file set!");
            this->application_config.logging_to_file_set = true;
        } else if (this->parsed_arguments[i] == "--file") {
            std::println("The file the user wants to run is {}", this->parsed_arguments[i+1]);
            if (this->parsed_arguments[i+1].contains(".mabin")) {
                this->application_config.mabin_file = this->parsed_arguments[i+1];
            } else {
                std::println("The file you parsed does not have the correct file format!");
                exit(-1); // Might make exit and error codes better and more expressive of what I am doing
            }
        }

    }

}