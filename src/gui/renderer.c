#include "renderer.h"

bool renderer_init(struct Renderer* self, struct SDL_Window* window) {
   self->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   self->font = TTF_OpenFont("ressources/fonts/Segoe-UI-Bold.ttf", 256);

   self->full_window = (SDL_Rect){0, 0, 1920, 1080};
   self->top_left = (SDL_Rect){0, 0, 525, 210};
   self->top_center = (SDL_Rect){525, 0, 870, 210};
   self->top_right = (SDL_Rect){1395, 0, 525, 210};
   self->left = (SDL_Rect){0, 210, 525, 870};
   self->center = (SDL_Rect){525, 210, 870, 870};
   self->right = (SDL_Rect){1395, 210, 525, 870};

   self->lines_threshold = 1;
   self->tile_size = 30;
   self->tile_outline = 2;


   //TODO:
   return true;
}

void load_text(struct Renderer* self, char* str, SDL_Color color, SDL_Rect rect) {
   SDL_Surface* surface = TTF_RenderText_Blended(self->font, str, color);
   if (self->font == NULL) {
      //TODO:
   }
   SDL_Texture* texture = NULL;
   if (surface != NULL) {
      texture = SDL_CreateTextureFromSurface(self->renderer, surface);
   }
   SDL_FreeSurface(surface);
   SDL_RenderCopy(self->renderer, texture, NULL, &rect);
   SDL_DestroyTexture(texture);
}

void draw_rect(struct Renderer* self, SDL_Rect rect, SDL_Color color) {
   SDL_SetRenderDrawColor(self->renderer, color.r, color.g, color.b, color.a);
   SDL_RenderFillRect(self->renderer, &rect);
}

void render_background(struct Renderer* self, int score) {

   SDL_Color color = {0x27, 0x27, 0x2c, 0xFF};
   SDL_Color line_color = {0xFF, 0xFF, 0xFF, 0xFF};
   SDL_Color text_color = {0xFF, 0xFF, 0xFF, 0xFF};
   SDL_Texture* text = NULL;
   SDL_Rect rectangle;

   draw_rect(self, self->center, color);
   draw_rect(self, self->top_center, color);


   color = (SDL_Color){0x18, 0x18, 0x18, 0xFF};
   draw_rect(self, self->top_left, color);
   draw_rect(self, self->left, color);
   draw_rect(self, self->top_right, color);
   draw_rect(self, self->right, color);

//TODO: draw_line function
   rectangle = (SDL_Rect){self->top_center.x - self->lines_threshold / 2, 0, self->lines_threshold, self->full_window.h};
   draw_rect(self, rectangle, line_color);
   rectangle = (SDL_Rect){self->top_right.x - self->lines_threshold / 2, 0, self->lines_threshold, self->full_window.h};
   draw_rect(self, rectangle, line_color);
   rectangle = (SDL_Rect){0, self->center.y - self->lines_threshold / 2, self->full_window.w, self->lines_threshold};
   draw_rect(self, rectangle, line_color);


   rectangle = (SDL_Rect){self->center.x + 200, 0, self->center.w - 400, self->center.y - 50};
   load_text(self, "PENTRIS", text_color, rectangle);

   rectangle = (SDL_Rect){self->center.x + self->center.w - 180, self->center.y - 110, 80, 24};
   load_text(self, "by Wiqiro", text_color, rectangle);

   char score_str[50];
   sprintf(score_str, "SCORE: %d", score);
   rectangle = (SDL_Rect){15, 0, 25 * strlen(score_str), 60};
   load_text(self, score_str, text_color, rectangle);

   SDL_DestroyTexture(text); 

}



void render_tile(struct Renderer* self, enum Tile tile, struct Coord pos) {
	SDL_Rect rectangle = {pos.x - self->tile_outline / 2, pos.y - self->tile_outline / 2, self->tile_size + self->tile_outline, self->tile_size + self->tile_outline};

   
	SDL_Color color = {0x1B, 0x18, 0x18, 0xFF};
   draw_rect(self, rectangle, color);

   rectangle = (SDL_Rect){pos.x + self->tile_outline / 2, pos.y + self->tile_outline / 2, self->tile_size - self->tile_outline, self->tile_size - self->tile_outline};
   switch (tile) {
   case RED:
	   color = (SDL_Color){0xFF, 0x00, 0x00, 0xFF};
      break;
   case BLUE:
	   color = (SDL_Color){0x00, 0x00, 0xFF, 0xFF};
      break;
   case GREEN:
	   color = (SDL_Color){0x00, 0xFF, 0x00, 0xFF};
      break;
   case YELLOW:
	   color = (SDL_Color){0xFF, 0xFF, 0x00, 0xFF};
      break;
   case ORANGE:
	   color = (SDL_Color){0xFF, 0xA5, 0x00, 0xFF};
      break;
   case PURPLE:
	   color = (SDL_Color){0xFF, 0x00, 0xFF, 0xFF};
      break;
   case AQUA:
	   color = (SDL_Color){0x00, 0xFF, 0xFF, 0xFF};
      break;
   default:
      break;
   }
   draw_rect(self, rectangle, color);
}



void render_map(struct Renderer* self, struct Map map) {

   struct Coord tile_pos;

   for (int j = 0; j < map.size; j++) {
      for (int i = 0; i < map.size; i++) {
         if (map.tiles[i][j] != NO_TILE) {
            tile_pos = (struct Coord){i * self->tile_size + self->center.x, j * self->tile_size + self->center.y};
            render_tile(self, map.tiles[i][j], tile_pos);
         }
      }
   }
}


   
void render_poly(struct Renderer* self, struct Polyomino poly) {

   struct Coord tile_pos;

   for (int j = 0; j < poly.mat_size; j++) {
      for (int i = 0; i < poly.mat_size; i++) {
         if (poly.tiles[i][j] != NO_TILE) {
            tile_pos = (struct Coord){ (poly.pos.x + i) * self->tile_size + self->center.x, (poly.pos.y + j) * self->tile_size + self->center.y};
            render_tile(self, poly.tiles[i][j], tile_pos);
         }
      }
   }
}
