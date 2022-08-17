#include <SDL.h>
#include <SDL_image.h>

struct State {
   SDL_Window window;
   SDL_Renderer renderer;
   clock_t timer;
};