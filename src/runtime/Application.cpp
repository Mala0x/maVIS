#include "Application.hpp"

#include <print>

void Application::init(int argc, char *argv[]) {
  this->arguments = new Arguments(argc, argv, this->application_config);

  this->file = new File(this->application_config);

  this->window = new Window();

  this->core = new Core(this->file->vector);

  std::println("verbose mode set: {}",
               this->application_config.verbose_mode_set);
}

void Application::loop() { core->delegation(); }

Application::~Application() {
  delete this->arguments;
  delete this->file;
  delete this->window;
  delete this->core;
  std::println("The heap allocated arguments where deleted!");
}
