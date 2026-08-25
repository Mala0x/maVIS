#pragma once

// My own custom hpp imports
#include "Common/Config.hpp"
#include "Core/Core.hpp"
#include "IO/Arguments/Arguments.hpp"
#include "IO/File/File.hpp"
#include "IO/Window/Window.hpp"

class Application {
private:
// Objects & structs live here
  Arguments *arguments = nullptr;
  File *file = nullptr;
  Window *window = nullptr;
  Core *core = nullptr;
  Config application_config;

// Helper functions live here
  static void get_signal(int signal); // This lets you press ctrl+c to close the program instead of having to kill the terminal that the process is running in lmao
public:
  void init(int argc, char *argv[]);
  void loop();
  ~Application();
};
