#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class Window {
private:
  SDL_Window *window_s = nullptr; // These two should be filled using the create window and renderer function from sdl3
  SDL_Renderer *renderer_s = nullptr; // Might need to chance the pointer things in this project to a c++ safe pointer alternative...
  SDL_Event event_s;
  TTF_TextEngine* text_engine_s = nullptr;
public:
  Window();
  void sdl_loop();
  ~Window();
};
