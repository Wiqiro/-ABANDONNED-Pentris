#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "structures.h"

enum Direction {
   UP,
   DOWN,
   LEFT,
   RIGHT,
};



struct Polyomino create_polyomino();

void generate_polyomino(struct Polyomino* poly);

void load_poly_from_file(FILE* file, struct Polyomino* poly);

bool polyomino_fall(struct Polyomino* poly, struct Map map, enum Direction dir);

void invert_poly(struct Polyomino* poly);

void poly_rotation_cw(struct Polyomino* poly);

void poly_rotation_ccw(struct Polyomino* poly);

void kill_polyomino(struct Polyomino* poly);

bool collision_test(struct Polyomino poly, struct Map map);

void spawn_poly(struct Polyomino* poly, int map_size, enum Direction side);
