#include "polyomino.h"


#include <stdio.h>

bool polyomino_fall(struct Polyomino* poly, struct Map map, enum Direction dir) {
   struct Polyomino tmp = *poly;

   switch (dir) {
   case UP:
      poly->pos.y--;
      break;
   case DOWN:
      poly->pos.y++;
      break;
   case LEFT:
      poly->pos.x--;
      break;
   case RIGHT:
      poly->pos.x++;
   }

   if (collision_test(*poly, map) == true) {
      *poly = tmp;
      return false;
   } else {
      return true;
   }

}

void poly_rotation_cw(struct Polyomino* poly) {
   struct Polyomino tmp;
   tmp.tiles = (enum Tile**)malloc(sizeof(enum Tile*) * 3);
   for (int i = 0; i < 3; i++) {
      tmp.tiles[i] = (enum Tile*)malloc(sizeof(enum Tile) * 3);
      for (int j = 0; j < 3; j++) {
         tmp.tiles[i][j] = poly->tiles[i][j];
      }
   }

   for (int i = 0; i < poly->mat_size; i++) {
      for (int j = 0; j < poly->mat_size; j++) {
         poly->tiles[i][j] = tmp.tiles[j][2 - i];
      }
   }
}


void poly_rotation_ccw(struct Polyomino* poly) {
   
   struct Polyomino tmp;
   tmp.tiles = (enum Tile**)malloc(sizeof(enum Tile*) * 3);
   for (int i = 0; i < 3; i++) {
      tmp.tiles[i] = (enum Tile*)malloc(sizeof(enum Tile) * 3);
      for (int j = 0; j < 3; j++) {
         tmp.tiles[i][j] = poly->tiles[i][j];
      }
   }

   for (int i = 0; i < poly->mat_size; i++) {
      for (int j = 0; j < poly->mat_size; j++) {
         poly->tiles[i][j] = tmp.tiles[2 - j][i];
      }
   }
}



bool collision_test(struct Polyomino poly, struct Map map) {
   int i = 0, j = 0;
   bool collision = false;
   while (i < poly.mat_size && collision == false) {
      if (poly.pos.x + i < map.max_w) {
         j = 0;
         while (j < poly.mat_size && collision == false) {
            if (poly.pos.y + j < map.max_h && poly.tiles[i][j] != NO_TILE) {
               if (map.tiles[poly.pos.x + i][poly.pos.y + j] != NO_TILE) {
                  collision = true;
               }
            }
            j++;
         }
      }
      i++;
   }
   return collision;
}

void spawn_poly(struct Polyomino poly, int map_size, enum Direction dir) {
   
}