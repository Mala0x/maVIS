#pragma once

#include "IO/Arguments/Arguments.hpp"
#include "Common/Config.h"

class Application {
    private:
        Arguments *arguments = nullptr;
        Config application_config;
    public:
        void init(int argc, char* argv[]);
        ~Application();
};