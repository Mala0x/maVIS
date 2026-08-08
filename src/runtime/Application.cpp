#include "Application.hpp"

#include <print>

void Application::init(int argc, char* argv[]) {
    this->arguments = new Arguments(argc, argv, this->application_config);

    std::println("verbose mode set: {}", this->application_config.verbose_mode_set);
}

Application::~Application() {
    delete this->arguments;
    std::println("The heap allocated arguments was deleted!");
}