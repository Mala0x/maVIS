#include "Window.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>

#include <SDL3/SDL_render.h>
#include <print>

Window::Window() {
    std::println("Going to init the sdl3 window!");

    bool set_metadata_success_s = SDL_SetAppMetadata("Virtual machine window", "0.0.01", "com.maVIS.window");

    if (!set_metadata_success_s) {
        std::print("Call to set app metadata SDL has failed! Error: {}", SDL_GetError()); // All these things should only be printed when verbose mode is set
    }

    bool init_sucess_s = SDL_Init(SDL_INIT_VIDEO);

    if (!init_sucess_s) {
        std::print("Call to init SDL & SDL_INIT_VIDEO has failed! Error: {}", SDL_GetError());
    }

    SDL_Window *window_s = nullptr; // These two should be filled using the create window and renderer function from sdl3
    SDL_Renderer *renderer_s = nullptr;

    bool create_window_renderer_success_s = SDL_CreateWindowAndRenderer("Virtual machine window", 800, 800, 0, &window_s, &renderer_s); //SDL_CreateWindowAndRenderer

    if (!create_window_renderer_success_s) {
        std::print("Call to create window and renderer in SDL3 has failed! Error: {}", SDL_GetError());
    }
}

Window::~Window() {
    // Delete and uninit all the sdl systems
    SDL_Quit();
}