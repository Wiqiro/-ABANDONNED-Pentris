#pragma once

#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "renderer.h"
#include "window.h"
#include "../game/structures.h"
#include "../game/polyomino.h"
#include "../game/map.h"

struct UI {
   
   struct Renderer renderer;
   struct Window window; 
   
   
   clock_t tick;
   clock_t timer;
};

bool initialize_ui();

void render(struct Renderer* renderer, struct Map map, struct Polyomino poly_l, struct Polyomino poly_r);