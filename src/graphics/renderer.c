#include "renderer.h"

void render_background(SDL_Renderer* renderer, struct Map map, struct Coord offset, int tile_size, int outline) {

   SDL_SetRenderDrawColor(renderer, 0x18, 0x18, 0x18, 0xFF);
   SDL_RenderFillRect(renderer, NULL);

   SDL_Rect square = {offset.x, offset.y, map.size * tile_size, map.size * tile_size};

   SDL_SetRenderDrawColor(renderer, 0x30, 0x30, 0x38, 0xFF);
   SDL_RenderFillRect(renderer, &square);

   SDL_Rect rectangle;
   SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

   rectangle = (SDL_Rect){square.x - outline, square.y - outline, outline, square.h + outline};
   SDL_RenderFillRect(renderer, &rectangle);

   rectangle = (SDL_Rect){square.x - outline, square.y - outline, square.h + outline, outline};
   SDL_RenderFillRect(renderer, &rectangle);

   rectangle = (SDL_Rect){square.x + square.w, square.y - outline, outline, square.w + outline * 2};
   SDL_RenderFillRect(renderer, &rectangle);

   rectangle = (SDL_Rect){square.x - outline, square.y + square.h, square.h + outline, outline};
   SDL_RenderFillRect(renderer, &rectangle);
}



void render_tile(SDL_Renderer* renderer, enum Tile tile, struct Coord pos, int tile_size, int outline) {
	SDL_Rect rectangle = {pos.x - outline / 2, pos.y - outline / 2, tile_size + outline, tile_size + outline};

   
	SDL_SetRenderDrawColor(renderer, 0x1B, 0x18, 0x18, 0xFF);
   SDL_RenderFillRect(renderer, &rectangle);

   rectangle = (SDL_Rect){pos.x + outline / 2, pos.y + outline / 2, tile_size - outline, tile_size - outline};
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



void render_map(SDL_Renderer* renderer, struct Map map, int tile_size, int tile_outline, struct Coord offset) {

   struct Coord tile_pos;

   for (int j = 0; j < map.max_h; j++) {
      for (int i = 0; i < map.max_w; i++) {
         if (map.tiles[i][j] != NO_TILE) {
            tile_pos = (struct Coord){i * tile_size + offset.x, j * tile_size + offset.y};
            render_tile(renderer, map.tiles[i][j], tile_pos, tile_size, tile_outline);
         }
      }
   }
}


   
void render_poly(SDL_Renderer* renderer, struct Polyomino poly, int tile_size, int tile_outline, struct Coord offset) {

   struct Coord tile_pos;

   for (int j = 0; j < poly.mat_size; j++) {
      for (int i = 0; i < poly.mat_size; i++) {
         if (poly.tiles[i][j] != NO_TILE) {
            tile_pos = (struct Coord){ (poly.pos.x + i) * tile_size + offset.x, (poly.pos.y + j) * tile_size + offset.y};
            render_tile(renderer, poly.tiles[i][j], tile_pos, tile_size, tile_outline);
         }
      }
   }
}