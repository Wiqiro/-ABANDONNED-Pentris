#include "structures.h"
#include "map.h"



struct Map create_and_initialize_map(int w, int h) {
   struct Map map;

   map.tiles = (enum Tile**)malloc(sizeof(enum Tile*) * w);
   if (map.tiles != NULL) {
      for (int i = 0; i < w; i++) {
         map.tiles[i] = (enum Tile*)malloc(sizeof(enum Tile) * h);
         if (map.tiles[i] != NULL) {
            for (int j = 0; j < h; j++) {
               map.tiles[i][j] = NO_TILE;
            }
         }
      }
   }
   map.centre = (struct Coord){w / 2, h / 2};
   map.tiles[w / 2][h / 2] = BASE;
   map.tiles[w / 2 + 1][h / 2] = BASE;
   map.tiles[w / 2 - 1][h / 2] = BASE;
   map.tiles[w / 2][h / 2 + 1] = BASE;
   map.tiles[w / 2][h / 2 - 1] = BASE;
   map.size = w;
   map.size = h;
   map.size = w;

   return map;
}

void merge_poly(struct Map* map, struct Polyomino poly) {
   for (int i = 0; i < poly.mat_size; i++) {
      for (int j  = 0; j < poly.mat_size; j++) {
         if (poly.tiles[i][j] != NO_TILE) {
            map->tiles[poly.pos.x + i][poly.pos.y + j] = poly.tiles[i][j];
         }
      }
   }
}

static bool is_rotation_allowed(struct Map* map) {

   return false;
}

bool map_rotation_cw(struct Map* map) {
   struct Map tmp;
   tmp.tiles = (enum Tile**)malloc(sizeof(enum Tile*) * map->size);
   for (int i = 0; i < map->size; i++) {
      tmp.tiles[i] = (enum Tile*)malloc(sizeof(enum Tile) * map->size);
      for (int j = 0; j < map->size; j++) {
         tmp.tiles[i][j] = map->tiles[i][j];
      }
   }

   for (int i = 0; i < map->size; i++) {
      for (int j = 0; j < map->size; j++) {
         map->tiles[i][j] = tmp.tiles[j][map->size - 1 - i];
      }
   }
   return is_rotation_allowed(map);
}

bool map_rotation_ccw(struct Map* map) {
   struct Map tmp;
   tmp.tiles = (enum Tile**)malloc(sizeof(enum Tile*) * map->size);
   for (int i = 0; i < map->size; i++) {
      tmp.tiles[i] = (enum Tile*)malloc(sizeof(enum Tile) * map->size);
      for (int j = 0; j < map->size; j++) {
         tmp.tiles[i][j] = map->tiles[i][j];
      }
   }

   for (int i = 0; i < map->size; i++) {
      for (int j = 0; j < map->size; j++) {
         map->tiles[i][j] = tmp.tiles[map->size -1- j][i];
      }
   }
   return is_rotation_allowed(map);
}

int detect_square(struct Map* map) {

   bool detected = true;

   int i = map->size / 2 - 2;
   while (i >= 0 && detected == true) {
      int j = i;
      detected = false;
      while (j < map->size - i - 1 && detected == false) {
         detected = (map->tiles[i][j] == NO_TILE 
                  || map->tiles[map->size - j - 1][i] == NO_TILE
                  || map->tiles[map->size - i - 1][map->size - j - 1] == NO_TILE
                  || map->tiles[j][map->size - i - 1] == NO_TILE);
         j++;
      }

      if (detected == false) {
         for (j = i; j < map->size - i - 1; j++) {
            map->tiles[i][j] = NO_TILE;
            map->tiles[map->size - j - 1][i] = NO_TILE;
            map->tiles[map->size - i - 1][map->size - j - 1] = NO_TILE;
            map->tiles[j][map->size - i - 1] = NO_TILE;
         }
      }
      i--;
   }
   if (i == -1) {
      return 0;
   } else {
      return map->size / 2 - i - 1;
   }
}

struct Vect get_vector_to_center(struct Map map, struct Coord pos) {
   return (struct Vect){map.size / 2 - pos.x, map.size / 2 - pos.y};
}

bool is_floating(struct Map map, struct Coord pos) {
   
   if (pos.x - 1 >= 0) {
      if (map.tiles[pos.x - 1][pos.y] != NO_TILE) {
         return false;
      }
   }
   if (pos.x + 1 <= map.size) {
      if (map.tiles[pos.x + 1][pos.y]) {
         return false;
      }
   }
   if (pos.y - 1 >= 0) {
      if (map.tiles[pos.x][pos.y - 1] != NO_TILE) {
         return false;
      }
   }
   if (pos.y + 1 < map.size) {
      if (map.tiles[pos.x][pos.y + 1] != NO_TILE) {
         return false;
      }
   }
   return true; 
}

void tile_fall(struct Map* map, struct Coord pos) {
   struct Vect vect = get_vector_to_center(*map, pos);

   if (abs(vect.x) == abs(vect.y)) {
      map->tiles[pos.x + abs(vect.x) / vect.x][pos.y + abs(vect.y) / vect.y] = map->tiles[pos.x][pos.y];
      map->tiles[pos.x ][pos.y] = NO_TILE;
   } else if (abs(vect.x) > abs(vect.y)) {
      if (map->tiles[pos.x + abs(vect.x) / vect.x][pos.y] == NO_TILE) {
         map->tiles[pos.x + abs(vect.x) / vect.x][pos.y] = map->tiles[pos.x][pos.y];
         map->tiles[pos.x ][pos.y] = NO_TILE;
      }
   } else {
      if (map->tiles[pos.x][pos.y + abs(vect.y) / vect.y] == NO_TILE) {
         map->tiles[pos.x][pos.y + abs(vect.y) / vect.y] = map->tiles[pos.x][pos.y];
         map->tiles[pos.x][pos.y] = NO_TILE;
      }
   }
}

void gravitation(struct Map* map, int dist) {

   int i = map->size / 2 - dist - 1;

   for (int j = i; j < map->size - i - 1; j++) {
      tile_fall(map, (struct Coord){i, j});
      tile_fall(map, (struct Coord){map->size - j - 1, i});
      tile_fall(map, (struct Coord){map->size - i - 1, map->size - j - 1});
      tile_fall(map, (struct Coord){j, map->size - i - 1});

   }
}