#ifndef POLYOMINO_H
#define POLYOMINO_H

#include <stdlib.h>
#include <stdbool.h>

#include "structures.h"

enum Direction {
   UP,
   DOWN,
   LEFT,
   RIGHT,
};

struct Polyomino create_and_generate_polyomino(int order);

void generate_polyomino(struct Polyomino* poly);

bool polyomino_fall(struct Polyomino* poly, struct Map map, enum Direction dir);

void poly_rotation_cw(struct Polyomino* poly);

void poly_rotation_ccw(struct Polyomino* poly);

void kill_polyomino(struct Polyomino* poly);

bool collision_test(struct Polyomino poly, struct Map map);


#endif