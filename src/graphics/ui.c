#include "ui.h"

static struct UI ui;


//TODO: handle multiple screens
bool initialize_ui() {
   if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
      SDL_Window* window = SDL_CreateWindow("Pentris", 0, 60, 1900, 1000, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
      if (window != NULL) {
         SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
         if (renderer != NULL) {
            ui.window = window;
            ui.renderer = renderer;
            SDL_GetCurrentDisplayMode(0, &(ui.DM));
            SDL_GetWindowSize(ui.window, &(ui.width), &(ui.height));
         }
      }
   }
}