#pragma once

#include "Common/Config.h"
#include "Core/Core.hpp"
#include "IO/Arguments/Arguments.hpp"
#include "IO/File/File.hpp"
#include "IO/Window/Window.hpp"

class Application {
private:
  Arguments *arguments = nullptr;
  File *file = nullptr;
  Window *window = nullptr;
  Core *core = nullptr;
  Config application_config;

public:
  void init(int argc, char *argv[]);
  void loop();
  ~Application();
};
