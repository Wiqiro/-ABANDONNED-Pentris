#pragma once

#include <time.h>

#include <SDL.h>

#include "../structures.h"
#include "../polyomino.h"
#include "../map.h"

struct UI {
   SDL_Window* window;
   SDL_Renderer* renderer;
   SDL_DisplayMode DM;

   
   int width;
   int height;
   bool fullscreen;

   int tile_size;
   int tile_outline;
   SDL_Rect map;
   int map_outline;
   
   
   clock_t tick;
   clock_t timer;
};