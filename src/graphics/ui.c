#include "ui.h"

static struct UI ui;


//TODO: handle multiple screens
bool initialize_ui() {

   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      return false;
   }
   IMG_Init(IMG_INIT_PNG);
   TTF_Init();
   SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2" );
   ui.window = SDL_CreateWindow("Pentris²", 0, 60, 1900, 2000, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
   if (ui.window == NULL) {
      return false;
   }
   SDL_SetWindowFullscreen(ui.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
   
   ui.renderer = SDL_CreateRenderer(ui.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if (ui.renderer == NULL) {
      return false;
   }

   ui.font_med = TTF_OpenFont("ressources/fonts/Segoe-UI-Bold.ttf", 256);

   SDL_GetCurrentDisplayMode(0, &(ui.DM));
   SDL_GetWindowSize(ui.window, &(ui.width), &(ui.height));
   ui.fullscreen = true;

   ui.content = (SDL_Rect){15, 15, 1890, 1080};
   ui.top_left = (SDL_Rect){0, 0, 525, 210};
   ui.top_centre = (SDL_Rect){525, 0, 870, 210};
   ui.top_right = (SDL_Rect){1395, 0, 525, 210};
   ui.map = (SDL_Rect){525, 210, 870, 870};

   ui.lines_threshold = 2;
   ui.tile_size = 30;
   ui.tile_outline = 4;
   return true;

}

void render(struct Map map, struct Polyomino poly) {
   SDL_RenderClear(ui.renderer);
   render_background(ui.renderer, ui.font_med, map, ui.map, ui.width, ui.height, ui.lines_threshold, 10254478);
   render_map(ui.renderer, map, ui.tile_size, ui.tile_outline, (struct Coord){ui.map.x, ui.map.y});
   render_poly(ui.renderer, poly, ui.tile_size, ui.tile_outline, (struct Coord){ui.map.x, ui.map.y});

   SDL_RenderPresent(ui.renderer);
}