#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "structures.h"
#include "polyomino.h"
#include "map.h"

void print_map(struct Map map, struct Polyomino poly) {
   printf("%d  %d\n", map.centre.x, map.centre.y);
   for (int j = 0; j < map.max_h; j++) {
      for (int i = 0; i < map.max_w; i++) {
         if (map.tiles[i][j] != NO_TILE) {
            printf("%d ", map.tiles[i][j]);
         
         } else {
            printf("  ");
         }
      }
      printf("\n");
   }
}

struct Polyomino get_test_poly() {
   struct Polyomino poly;
   poly.mat_size = 3;


   poly.tiles = (enum Tile**)malloc(sizeof(enum Tile*) * 3);
   for (int i = 0; i < poly.mat_size; i++) {
      poly.tiles[i] = (enum Tile*)malloc(sizeof(enum Tile) * 3);
      for (int j = 0; j < poly.mat_size; j++) {
         poly.tiles[i][j] = NO_TILE;
      }
   }
   poly.pos = (struct Coord){50, 13};

   enum Tile color = rand()%COLOR_TOTAL;

   poly.tiles[0][1] = color;
   poly.tiles[1][1] = color;
   poly.tiles[2][1] = color;
   poly.tiles[0][2] = color;

   return poly;  
}

struct Coord offset = {526, 106};
int tile_size = 28;
int border_size = 4;
int outline_size = 2;



void render_background(SDL_Renderer* renderer, struct Map map) {

   SDL_SetRenderDrawColor(renderer, 0x1B, 0x18, 0x18, 0xFF);
   SDL_RenderFillRect(renderer, NULL);

   SDL_Rect square = {offset.x, offset.y, map.size * tile_size, map.size * tile_size};

   SDL_SetRenderDrawColor(renderer, 0x28, 0x2a, 0x2e, 0xFF);
   SDL_RenderFillRect(renderer, &square);

   SDL_Rect rectangle;
   SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

   rectangle = (SDL_Rect){square.x - outline_size, square.y - outline_size, outline_size, square.h + outline_size};
   SDL_RenderFillRect(renderer, &rectangle);

   rectangle = (SDL_Rect){square.x - outline_size, square.y - outline_size, square.h + outline_size, outline_size};
   SDL_RenderFillRect(renderer, &rectangle);

   rectangle = (SDL_Rect){square.x + square.w, square.y - outline_size, outline_size, square.w + outline_size * 2};
   SDL_RenderFillRect(renderer, &rectangle);

   rectangle = (SDL_Rect){square.x - outline_size, square.y + square.h, square.h + outline_size, outline_size};
   SDL_RenderFillRect(renderer, &rectangle);
}

void render_tile(SDL_Renderer* renderer, enum Tile tile, struct Coord pos) {
	SDL_Rect rectangle = {tile_size * pos.x - border_size / 2 + offset.x, tile_size * pos.y - border_size / 2 + offset.y,
                        tile_size + border_size, tile_size + border_size};

   
	SDL_SetRenderDrawColor(renderer, 0x1B, 0x18, 0x18, 0xFF);
   SDL_RenderFillRect(renderer, &rectangle);

   rectangle = (SDL_Rect){tile_size * pos.x + border_size / 2 + offset.x, tile_size * pos.y + border_size / 2 + offset.y,
                        tile_size - border_size, tile_size - border_size};
   switch (tile) {
   case RED:
	   SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
      break;
   case BLUE:
	   SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
      break;
   case GREEN:
	   SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
      break;
   case YELLOW:
	   SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
      break;
   case ORANGE:
	   SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF);
      break;
   case PURPLE:
	   SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
      break;
   case AQUA:
	   SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
      break;
   default:
      break;
   }
   SDL_RenderFillRect(renderer, &rectangle);
}

void render_map(SDL_Renderer* renderer, struct Map map) {
   SDL_RenderClear(renderer);   
   render_background(renderer, map);
   for (int j = 0; j < map.max_h; j++) {
      for (int i = 0; i < map.max_w; i++) {
         if (map.tiles[i][j] != NO_TILE) {
            render_tile(renderer, map.tiles[i][j], (struct Coord){i, j});
         }
      }
   }
}


void render_poly(SDL_Renderer* renderer, struct Polyomino poly) {
   for (int j = 0; j < poly.mat_size; j++) {
      for (int i = 0; i < poly.mat_size; i++) {
         if (poly.tiles[i][j] != NO_TILE) {
            render_tile(renderer, poly.tiles[i][j], (struct Coord){poly.pos.x + i, poly.pos.y + j});
         }
      }
   }
}