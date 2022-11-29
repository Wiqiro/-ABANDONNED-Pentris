#pragma once

#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "renderer.h"
#include "window.h"
#include "../game/structures.h"
#include "../game/polyomino.h"
#include "../game/map.h"

struct UI {
   
   struct Renderer renderer;
   struct Window window; 
};

bool initialize_ui();
void render(struct Renderer* renderer, struct Map map, struct Polyomino poly_l, struct Polyomino poly_r);