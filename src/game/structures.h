#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdint.h>

enum Tile {
   RED,
   BLUE,
   GREEN,
   YELLOW,
   ORANGE,
   PURPLE,
   AQUA,

   COLOR_TOTAL,
   BASE,
   NO_TILE,
};

struct Coord {
   int32_t x;
   int32_t y;
};



struct Polyomino {
   enum Tile** tiles;
   struct Coord pos;
   int32_t mat_size;
};


struct Map {
   enum Tile** tiles;
   struct Coord centre;
   int size;
};

#endif