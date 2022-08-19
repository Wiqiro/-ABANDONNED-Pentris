#include "renderer.h"


void load_text(TTF_Font* font, SDL_Renderer* renderer, char* str, SDL_Color color, SDL_Rect rect) {
   SDL_Surface* surface = TTF_RenderText_Blended(font, str, color);
   if (font == NULL) {
      printf("a");
   }
   SDL_Texture* texture = NULL;
   if (surface != NULL) {
      texture = SDL_CreateTextureFromSurface(renderer, surface);
   }
   SDL_FreeSurface(surface);
   SDL_RenderCopy(renderer, texture, NULL, &rect);
   SDL_DestroyTexture(texture);
}

void render_background(SDL_Renderer* renderer, TTF_Font* font, struct Map map, SDL_Rect container, int win_w, int win_h, int outline, int score) {

   SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF};
   SDL_Texture* text = NULL;
   SDL_Rect rectangle;

   SDL_SetRenderDrawColor(renderer, 0x27, 0x27, 0x2c, 0xFF);
   SDL_RenderFillRect(renderer, &container);
   rectangle = (SDL_Rect){container.x, 0, container.w, container.y};
   SDL_RenderFillRect(renderer, &rectangle);


   SDL_SetRenderDrawColor(renderer, 0x18, 0x18, 0x18, 0xFF);
   rectangle = (SDL_Rect){0, 0, container.x, win_h};
   SDL_RenderFillRect(renderer, &rectangle);
   rectangle = (SDL_Rect){container.x + container.w, 0, container.x, win_h};
   SDL_RenderFillRect(renderer, &rectangle);


   SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   rectangle = (SDL_Rect){container.x, 0, outline, win_h};
   SDL_RenderFillRect(renderer, &rectangle);
   rectangle = (SDL_Rect){0, container.y - outline, win_w, outline};
   SDL_RenderFillRect(renderer, &rectangle);
   rectangle = (SDL_Rect){container.x + container.w, 0, outline, win_h};
   SDL_RenderFillRect(renderer, &rectangle);

   rectangle = (SDL_Rect){container.x + 200, 0, container.w - 400, container.y - 50};
   load_text(font, renderer, "PENTRIS", color, rectangle);

   rectangle = (SDL_Rect){container.x + container.w - 180, container.y - 110, 80, 24};
   load_text(font, renderer, "by Wiqiro", color, rectangle);

   char score_str[50];
   sprintf(score_str, "SCORE: %d", score);
   rectangle = (SDL_Rect){15, 0, 25 * strlen(score_str), 60};
   load_text(font, renderer, score_str, color, rectangle);

   SDL_DestroyTexture(text); 

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
