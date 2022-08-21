#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "game/structures.h"
#include "game/polyomino.h"
#include "game/map.h"
#include "gui/ui.h"
#include "gui/renderer.h"

struct UI ui;

int main(int argc, char* argv[]) {

   srand(time(NULL));
   initialize_ui(&ui);


   int w = 29, h = 29;
   bool game_over = false;
   int tick = 400;

   struct Map map = create_and_initialize_map(w, h);
   struct Polyomino poly_r = create_polyomino(), poly_l = create_polyomino();
   FILE* file = fopen("ressources/polynomioes/4-ominoes", "r");
   if (file != NULL) {
      load_poly_from_file(file, &poly_r);
      load_poly_from_file(file, &poly_l);
   }
   spawn_poly(&poly_l, map.size, LEFT);
   spawn_poly(&poly_r, map.size, RIGHT);
   
   clock_t timer = clock();

   while (game_over == false) {
      
      handle_events(&ui.window);
      if (ui.window.action[MAP_ROTATION_CW] == PRESSED) {
         map_rotation_cw(&map);
      }
      if (ui.window.action[MAP_ROTATION_CCW] == PRESSED) {
         map_rotation_ccw(&map);
      }
      if (ui.window.action[POLY_ROTATION_LEFT] == PRESSED) {
         if (ui.window.action[POLY_INVERT_ROTATION] == NONE) {
            poly_rotation_cw(&poly_l);
         } else {
            poly_rotation_ccw(&poly_l);
         }
      }
      if (ui.window.action[POLY_ROTATION_RIGHT] == PRESSED) {
         if (ui.window.action[POLY_INVERT_ROTATION] == NONE) {
            poly_rotation_cw(&poly_r);
         } else {
            poly_rotation_ccw(&poly_r);
         }
      }
      if (ui.window.action[POLY_UP] == PRESSED) {
         polyomino_fall(&poly_l, map, UP);
         polyomino_fall(&poly_r, map, UP);
      }
      if (ui.window.action[POLY_DOWN] == PRESSED) {
         polyomino_fall(&poly_l, map, DOWN);
         polyomino_fall(&poly_r, map, DOWN);
      }
      if (ui.window.action[POLY_SPEEDUP] == NONE) {
         tick = 400;
      } else {
         tick = 40;
      }
      if (ui.window.action[QUIT] != NONE) {
         game_over = true;
      }
     

      if (clock() - timer >= tick) {
         if (polyomino_fall(&poly_r, map, LEFT) == false) {
            merge_poly(&map, poly_r);
            load_poly_from_file(file, &poly_r);
            spawn_poly(&poly_r, map.size, RIGHT);
         }
         if (polyomino_fall(&poly_l, map, RIGHT) == false) {
            merge_poly(&map, poly_l);
            load_poly_from_file(file, &poly_l);
            spawn_poly(&poly_l, map.size, LEFT);
         }
         timer = clock();
         int dist_detected = detect_square(&map);
         if (dist_detected > 0) {
            for (int i = dist_detected; i < map.size / 2 ; i++) {
               gravitation(&map, i);
            }
         }
      }

      render(&ui.renderer, map, poly_l, poly_r);
   }


   return EXIT_SUCCESS;
}