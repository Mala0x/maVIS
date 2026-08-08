#pragma once

#include <string>
namespace mavis {

    class ArgumentHandler {
        private:
        struct Config {
            std::string file_name;
            bool verbose_mode_set;
            bool headless_mode_set;
            bool debug_mode_set;
        };

        public:
            void init();
    };

}