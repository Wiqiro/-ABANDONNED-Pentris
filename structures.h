#ifndef STRUCTURES_H
#define STRUCTURES_H

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
   int x;
   int y;
};



struct Polyomino {
   enum Tile** tiles;
   struct Coord pos;
   int mat_size;
};


struct Map {
   enum Tile** tiles;
   struct Coord centre;
   int max_w;
   int max_h;
   int size;
};

#endif