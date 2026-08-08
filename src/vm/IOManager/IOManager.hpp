#pragma once

namespace mavis {

    class IOManager {
        private:

        public:
        
            struct Config { // Default to false set to true using command line arguments
                bool verbose_mode_set = false; // Verbose output towards the standard out stream
                bool debug_mode_set = false; // Make it so you manually step through the code (probably cannot mix with headless mode but that is for the future)
                bool headless_mode_set = false; // Future proofing for when I introduce the sdl3 window
            };

    };

}