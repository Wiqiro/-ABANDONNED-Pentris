#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../structures.h"

void load_text(TTF_Font* font, SDL_Renderer* renderer, char* str, SDL_Color color, SDL_Rect rect);

void render_background(SDL_Renderer* renderer, TTF_Font* font, struct Map map, SDL_Rect container, int win_w, int win_h, int outline, int score);

void render_tile(SDL_Renderer* renderer, enum Tile tile, struct Coord pos, int tile_size, int outline);

void render_map(SDL_Renderer* renderer, struct Map map, int tile_size, int tile_outline, struct Coord offset);

void render_poly(SDL_Renderer* renderer, struct Polyomino poly, int tile_size, int tile_outline, struct Coord offset);
