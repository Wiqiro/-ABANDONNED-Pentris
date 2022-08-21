#include "polyomino.h"




struct Polyomino create_polyomino() {

   return (struct Polyomino){NULL, {0, 0}, 0};
}


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

   if (collision_test(*poly, map) == true || poly->pos.y < 0 || poly->pos.y + poly->mat_size > map.size) {
      *poly = tmp;
      return false;
   } else {
      return true;
   }
}


void load_poly_from_file(FILE* file, struct Polyomino* poly) {

   if (file != NULL) {
      rewind(file);
      char buffer[100];
      fscanf(file, "%100[^[]", buffer);
      fscanf(file, "[%100[^]]", buffer);
      int n = strtol(buffer, NULL, 10);
      int line = rand()%n;

      for (int i = 0; i <= line; i++) {
         fscanf(file, "\n%100[^\n]", buffer);
      }

      fscanf(file, "%100[^[]", buffer);
      fscanf(file, "[%100[^]]", buffer);
      int size = strtol(buffer, NULL, 10);

      poly->mat_size = size;
      poly->tiles = (enum Tile**)calloc(size, sizeof(enum Tile*));
      if (poly->tiles != NULL) {
         for (int i = 0; i < size; i++) {
            poly->tiles[i] = (enum Tile*)calloc(size, sizeof(enum Tile));
            if (poly->tiles != NULL) {
               for (int j = 0; j < size; j++) {
                  poly->tiles[i][j] = NO_TILE;
               }
            } else {
               fprintf(stderr, "ERROR WHILE LOADING THE POLYNOMIAL");
            }
         }
      } else {
         fprintf(stderr, "ERROR WHILE LOADING THE POLYNOMIAL");
      }

      fscanf(file, "%100[^{]", buffer);
      fscanf(file, "{%100[^}]", buffer);

      char* token = strtok(buffer, "/");

      enum Tile color = rand()%COLOR_TOTAL;

      while (token != NULL) {
         int i, j;
         sscanf(token, "%d,%d", &i, &j);
         poly->tiles[i][j] = color;
         token = strtok(NULL, "/");
      }
   }

}



//TODO: implement better rotation algorithm
void poly_rotation_cw(struct Polyomino* poly) {
   struct Polyomino tmp;
   tmp.tiles = (enum Tile**)malloc(sizeof(enum Tile*) * poly->mat_size);
   for (int i = 0; i < poly->mat_size; i++) {
      tmp.tiles[i] = (enum Tile*)malloc(sizeof(enum Tile) * poly->mat_size);
      for (int j = 0; j < poly->mat_size; j++) {
         tmp.tiles[i][j] = poly->tiles[i][j];
      }
   }

   for (int i = 0; i < poly->mat_size; i++) {
      for (int j = 0; j < poly->mat_size; j++) {
         poly->tiles[i][j] = tmp.tiles[j][poly->mat_size - i - 1];
      }
   }
}


void poly_rotation_ccw(struct Polyomino* poly) {
   
   struct Polyomino tmp;
   tmp.tiles = (enum Tile**)malloc(sizeof(enum Tile*) * poly->mat_size);
   for (int i = 0; i < poly->mat_size; i++) {
      tmp.tiles[i] = (enum Tile*)malloc(sizeof(enum Tile) * poly->mat_size);
      for (int j = 0; j < poly->mat_size; j++) {
         tmp.tiles[i][j] = poly->tiles[i][j];
      }
   }

   for (int i = 0; i < poly->mat_size; i++) {
      for (int j = 0; j < poly->mat_size; j++) {
         poly->tiles[i][j] = tmp.tiles[poly->mat_size - j - 1][i];
      }
   }
}



bool collision_test(struct Polyomino poly, struct Map map) {
   int i = 0, j = 0;
   bool collision = false;
   while (i < poly.mat_size && collision == false) {
      if (poly.pos.x + i < map.size && poly.pos.x + i >= 0) {
         j = 0;
         while (j < poly.mat_size && j >= 0 && collision == false) {
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

void spawn_poly(struct Polyomino* poly, int map_size, enum Direction side) {
   poly->pos.y = map_size / 2;
   if (side == LEFT) {
      poly->pos.x = -poly->mat_size - 18;
   } else {
      poly->pos.x = map_size + 18;
   }
}