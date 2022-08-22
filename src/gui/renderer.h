#ifndef RENDERER_H
#define RENDERER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../game/structures.h"


struct Renderer {
   SDL_Renderer* renderer;
   TTF_Font* font;

   SDL_Rect full_window;
   SDL_Rect top_left;
   SDL_Rect top_center;
   SDL_Rect top_right;
   SDL_Rect left;
   SDL_Rect center;
   SDL_Rect right;

   uint8_t lines_threshold;
   uint8_t tile_size;
   uint8_t tile_outline;
};

bool renderer_init(struct Renderer* self, struct SDL_Window* window);

void load_text(struct Renderer* self, char* str, SDL_Color color, SDL_Rect rect);

void render_background(struct Renderer* self, int score);

void render_tile(struct Renderer* self, enum Tile tile, struct Coord pos);

void render_map(struct Renderer* self, struct Map map);

void render_poly(struct Renderer* self, struct Polyomino poly);

#endif