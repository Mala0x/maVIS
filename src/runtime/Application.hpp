#pragma once

#include "IO/Arguments/Arguments.hpp"
#include "IO/File/File.hpp"
#include "Core/Core.hpp"
#include "Common/Config.h"

class Application {
    private:
        Arguments *arguments = nullptr;
        File *file = nullptr;
        Core *core = nullptr;
        Config application_config;
    public:
        void init(int argc, char* argv[]);
        void loop();
        ~Application();
};