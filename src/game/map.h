#ifndef MAIN_BLOCK_H
#define MAIN_BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Vect {
   int x;
   int y;
};

struct Map create_and_initialize_map(int w, int h);

void merge_poly(struct Map* map, struct Polyomino poly);

bool map_rotation_cw(struct Map* map);

bool map_rotation_ccw(struct Map* map);

int detect_square(struct Map* map);

struct Vect get_vector_to_center(struct Map map, struct Coord pos);

void tile_fall(struct Map* map, struct Coord pos);

void gravitation(struct Map* map, int dist);

#endif