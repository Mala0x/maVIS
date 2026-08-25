#include "Window.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>

#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <print>

Window::Window() {
    std::println("Going to init the sdl3 window!");
    
    bool init_sucess_s = SDL_Init(SDL_INIT_VIDEO);

    bool ttf_init_succes_s = TTF_Init();

    if (!ttf_init_succes_s) {
        std::print("Call to init SDL_TTF has failed! Error: {}", SDL_GetError());
    }

    if (!init_sucess_s) {
        std::print("Call to init SDL & SDL_INIT_VIDEO has failed! Error: {}", SDL_GetError());
    }

    bool set_metadata_success_s = SDL_SetAppMetadata("Virtual machine window", "0.0.01", "com.maVIS.window");

    if (!set_metadata_success_s) {
        std::print("Call to set app metadata SDL has failed! Error: {}", SDL_GetError()); // All these things should only be printed when verbose mode is set
    }

    this->window_s = nullptr; // These two should be filled using the create window and renderer function from sdl3
    this->renderer_s = nullptr; // Might need to chance the pointer things in this project to a c++ safe pointer alternative...

    bool create_window_renderer_success_s = SDL_CreateWindowAndRenderer("Virtual machine window", 800, 800, 0, &this->window_s, &this->renderer_s); //SDL_CreateWindowAndRenderer

    if (!create_window_renderer_success_s) {
        std::print("Call to create window and renderer in SDL3 has failed! Error: {}", SDL_GetError());
    }

    this->text_engine_s = TTF_CreateRendererTextEngine(this->renderer_s);

    if (this->text_engine_s == nullptr) {
        std::print("Creating a textengine failed! Error: {}", SDL_GetError());
    }
}

void Window::sdl_loop() {

    // All the text rendering and stuff is just being done for testing purposes to see how and what and if it even works
    // It is pretty nice that sdl3 is working in such a limited enviroment 

    TTF_Font *my_font_s = nullptr;

    my_font_s = TTF_OpenFont("/usr/share/fonts/HackNerdFont-Regular.ttf", 24);

    auto text = TTF_CreateText(this->text_engine_s, my_font_s, "Hello, world!", 12);

    TTF_SetTextColor(text, 12, 126, 255, 255);

    while (true) {

        SDL_PollEvent(&this->event_s);

        if (this->event_s.type == SDL_EVENT_QUIT) { // Break out of the loop when an quit event is called and gracefully quit
            break;
        }

        SDL_SetRenderDrawColor(this->renderer_s, 255, 125, 255, 255);
        SDL_RenderClear(this->renderer_s);

        TTF_DrawRendererText(text, 25, 25);

        SDL_RenderPresent(this->renderer_s); // This has to always be called last

        std::print("Error?: {}\n", SDL_GetError());
    }
    exit(1); // Closes the program hopefully gracefully
}

Window::~Window() {
    // Delete and un-init all the sdl systems
    SDL_Quit();
    TTF_Quit();
}