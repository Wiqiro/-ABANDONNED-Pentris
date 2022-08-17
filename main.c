#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>

#include "structures.h"
#include "polyomino.h"
#include "map.h"


#include "testing.h"

struct Keyboard {
   int S, Z, E, D, SPACE, LEFT, RIGHT;
};

int main(int argc, char* argv[]) {

   SDL_Init(SDL_INIT_VIDEO);
   SDL_Window* window = SDL_CreateWindow("Pentris", 0, 60, 1900, 1000, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
   SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
   SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   SDL_Event event;

   srand(time(NULL));

   struct Keyboard keyboard = {0, 0, 0, 0, 0};

   int w = 31, h = 31;
   bool game_over = false;
   int tick = 400;

   struct Map map = create_and_initialize_map(w, h);
  // struct Polyomino poly_l = get_test_poly();
   struct Polyomino poly_r = get_test_poly();
   
   clock_t timer = clock();

//poly_rotation_cw(&poly);
   while (game_over == false) {

      while (SDL_PollEvent(&event) != 0) {
         if (event.type == SDL_QUIT) {
            game_over = true;
         } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_s:
               if (keyboard.S == 0) {
                  polyomino_fall(&poly_r, map, DOWN);
                  keyboard.S = 1;
               }
               break;
            case SDLK_z:
               if (keyboard.Z == 0) {
                  polyomino_fall(&poly_r, map, UP);
                  keyboard.Z = 1;  
               }
               break;
            case SDLK_e:
               if (keyboard.E == 0) {
                  poly_rotation_cw(&poly_r);
                  keyboard.E = 1;
               }
               break;
            case SDLK_d:
               if (keyboard.D == 0) {
                  poly_rotation_ccw(&poly_r);
                  keyboard.D = 1;
               }
               break;
            case SDLK_LEFT:
               if (keyboard.LEFT == 0) {
                  map_rotation_ccw(&map);
                  keyboard.LEFT = 1;
               }
               break;
            case SDLK_RIGHT:
               if (keyboard.RIGHT == 0) {
                  map_rotation_cw(&map);
                  keyboard.RIGHT = 1;
               }
               break;
            case SDLK_SPACE:
               if (keyboard.SPACE == 0) {
                  tick = 10;
                  keyboard.SPACE = 1;
               }
               break;
            default:
               break;
            }
         } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
            case SDLK_s:
               keyboard.S = 0;
               break;
            case SDLK_z:
               keyboard.Z = 0;
               break;
            case SDLK_e:
               keyboard.E = 0;
               break;
            case SDLK_d:
               keyboard.D = 0;
               break;
            case SDLK_SPACE:
               tick = 400;
               keyboard.SPACE = 0;
               break;
            case SDLK_LEFT:
               keyboard.LEFT = 0;
               break;
            case SDLK_RIGHT:
               keyboard.RIGHT = 0;
               break;
            default:
               break;
            }
         }
      }

      if (clock() - timer >= tick) {
         if (polyomino_fall(&poly_r, map, LEFT) == false) {
            merge_poly(&map, poly_r);
            poly_r = get_test_poly();
         }
         timer = clock();
         int dist_detected = detect_square(&map);
         if (dist_detected > 0) {
            for (int i = dist_detected; i < map.size / 2 ; i++) {
               gravitation(&map, i);
            }
         }
      }
      render_map(renderer, map);

      render_poly(renderer, poly_r);


      SDL_RenderPresent(renderer);
   }


   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);

   return EXIT_SUCCESS;
}