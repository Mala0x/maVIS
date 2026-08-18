#pragma once

#include <string>
#include <vector>

#include "../../Common/Config.hpp"

class Arguments {
    private:
        std::vector<std::string> parsed_arguments;
        Config &application_config;
        void parse_arguments();
    public:
        Arguments(int argc, char* argv[], Config &application_config); // Grabs the arguments the user passed
};