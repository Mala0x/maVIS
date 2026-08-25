#include "Application.hpp"

#include <print>
#include <csignal>

void Application::init(int argc, char *argv[]) {
  this->arguments = new Arguments(argc, argv, this->application_config);

  this->file = new File(this->application_config);

  if (!this->application_config.headless_mode_set) {
    this->window = new Window(); // Do not even init the memory when we will not be using the window
  }

  this->core = new Core(this->file->vector);

  std::println("verbose mode set: {}",
               this->application_config.verbose_mode_set);
}

// For now the signal processor does not actually check the signal, if it got a signal it just kills the process 
// Might actually need to do some checking of signals to correctly respond to them and what the would want

void Application::get_signal(int signal) {
  std::println("I have encountered a signal, signal: {}", signal);
  exit(signal); // This hopefully gracefully closes the program and exits normally when the user presses ctrl+c
}

void Application::loop() {
  signal(SIGINT, get_signal); // Checks if we need to close the program and actually close the program xD
  
  if (!this->application_config.headless_mode_set) {
    window->sdl_loop();
  }
  
  core->delegation();
}

Application::~Application() {
  delete this->arguments;
  delete this->file;

  if (!this->application_config.headless_mode_set) {
    delete this->window; // Never delete something that did not even exist!
  }
  
  delete this->core;
  std::println("The heap allocated arguments where deleted!");
}
