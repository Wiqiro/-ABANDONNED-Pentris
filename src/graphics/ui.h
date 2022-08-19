#pragma once

#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "renderer.h"
#include "../structures.h"
#include "../polyomino.h"
#include "../map.h"

struct UI {
   SDL_Window* window;
   SDL_Renderer* renderer;
   TTF_Font* font_small;
   TTF_Font* font_med;
   SDL_DisplayMode DM;



   int width;
   int height;
   bool fullscreen;


   SDL_Rect content;
   SDL_Rect top_left;
   SDL_Rect top_centre;
   SDL_Rect top_right;
   SDL_Rect map;

   int lines_threshold;
   int tile_size;
   int tile_outline;
   
   
   clock_t tick;
   clock_t timer;
};

bool initialize_ui();

void render(struct Map map, struct Polyomino poly);

