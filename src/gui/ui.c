#include "ui.h"


//TODO: handle multiple screens
bool initialize_ui(struct UI* self) {

   
   
   window_init(&self->window);
   renderer_init(&self->renderer, self->window.window);


   return true;

}

void render(struct Renderer* renderer, struct Map map, struct Polyomino poly_l, struct Polyomino poly_r) {
   SDL_RenderClear(renderer->renderer);
   render_background(renderer, 10254478);
   render_map(renderer, map);
   render_poly(renderer, poly_l);
   render_poly(renderer, poly_r);

   SDL_RenderPresent(renderer->renderer);
}