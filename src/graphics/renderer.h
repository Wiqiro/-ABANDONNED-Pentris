#pragma once

#include "../structures.h"
#include <SDL.h>



void render_background(SDL_Renderer* renderer, struct Map map, struct Coord offset, int tile_size, int outline);

void render_tile(SDL_Renderer* renderer, enum Tile tile, struct Coord pos, int tile_size, int outline);

void render_map(SDL_Renderer* renderer, struct Map map, int tile_size, int tile_outline, struct Coord offset);

void render_poly(SDL_Renderer* renderer, struct Polyomino poly, int tile_size, int tile_outline, struct Coord offset);
