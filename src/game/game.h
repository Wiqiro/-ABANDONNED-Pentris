#include "structures.h"

#include <stdint.h>
#include <time.h>


struct Game {
   struct Map map;
   struct Polyomino poly_l, poly_r, inc_l, inc_r;

   uint32_t score;
   uint32_t claimed_tiles;
   uint32_t spawned_polys;

   uint32_t tick, speed_tick;
   clock_t last_tick;
   bool speedup;

   bool active;
   bool menu;
};