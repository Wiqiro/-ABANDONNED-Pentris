#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <SDL.h>
#include <SDL_ttf.h>


#include "state.h"
#include "game/structures.h"
#include "game/polyomino.h"
#include "game/map.h"
#include "gui/ui.h"
#include "gui/renderer.h"

struct State state;

int main(int argc, char* argv[]) {

   srand(time(NULL));
   window_init(&state.window);
   renderer_init(&state.renderer, state.window.window);


   int w = 29, h = 29;
   bool game_over = false;
   int tick = 400;

   state.game.map = create_and_initialize_map(w, h);
   state.game.poly_r = create_polyomino();
   state.game.poly_l = create_polyomino();

   
   FILE* file = fopen("ressources/polynomioes/polyominoes", "r");
   if (file != NULL) {
      load_poly_from_file(file, &state.game.poly_r);
      load_poly_from_file(file, &state.game.poly_l);
   }
   spawn_poly(&state.game.poly_l, state.game.map.size, LEFT);
   spawn_poly(&state.game.poly_r, state.game.map.size, RIGHT);
   
   clock_t timer = clock();

   while (game_over == false) {
      
      handle_events(&state.window);
      if (state.window.action[MAP_ROTATION_CW] == PRESSED) {
         map_rotation_cw(&state.game.map);
      }
      if (state.window.action[MAP_ROTATION_CCW] == PRESSED) {
         map_rotation_ccw(&state.game.map);
      }
      if (state.window.action[POLY_ROTATION_LEFT] == PRESSED) {
         if (state.window.action[POLY_INVERT_ROTATION] == NONE) {
            poly_rotation_cw(&state.game.poly_l);
         } else {
            poly_rotation_ccw(&state.game.poly_l);
         }
      }
      if (state.window.action[POLY_ROTATION_RIGHT] == PRESSED) {
         if (state.window.action[POLY_INVERT_ROTATION] == NONE) {
            poly_rotation_cw(&state.game.poly_r);
         } else {
            poly_rotation_ccw(&state.game.poly_r);
         }
      }
      if (state.window.action[POLY_UP] == PRESSED) {
         polyomino_fall(&state.game.poly_l, state.game.map, UP);
         polyomino_fall(&state.game.poly_r, state.game.map, UP);
      }
      if (state.window.action[POLY_DOWN] == PRESSED) {
         polyomino_fall(&state.game.poly_l, state.game.map, DOWN);
         polyomino_fall(&state.game.poly_r, state.game.map, DOWN);
      }
      if (state.window.action[POLY_SPEEDUP] == NONE) {
         tick = 400;
      } else {
         tick = 40;
      }
      if (state.window.action[QUIT] != NONE) {
         game_over = true;
      }
     

      if (clock() - timer >= tick) {
         if (polyomino_fall(&state.game.poly_r, state.game.map, LEFT) == false) {
            merge_poly(&state.game.map, state.game.poly_r);
            load_poly_from_file(file, &state.game.poly_r);
            spawn_poly(&state.game.poly_r, state.game.map.size, RIGHT);
         }
         if (polyomino_fall(&state.game.poly_l, state.game.map, RIGHT) == false) {
            merge_poly(&state.game.map, state.game.poly_l);
            load_poly_from_file(file, &state.game.poly_l);
            spawn_poly(&state.game.poly_l, state.game.map.size, LEFT);
         }
         timer = clock();
         int dist_detected = detect_square(&state.game.map);
         if (dist_detected > 0) {
            for (int i = dist_detected; i < state.game.map.size / 2 ; i++) {
               gravitation(&state.game.map, i);
            }
         }
      }

      render(&state.renderer, state.game.map, state.game.poly_l, state.game.poly_r);
   }


   return EXIT_SUCCESS;
}