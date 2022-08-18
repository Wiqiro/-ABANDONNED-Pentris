#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "structures.h"
#include "polyomino.h"
#include "map.h"

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
