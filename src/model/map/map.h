#include <stdio.h>
#include <stdlib.h>

#ifndef MAP
#define MAP

#define MAX_CHAR 3

typedef struct floor {
    int id;
    char **cells;
} floor;

typedef struct map {
    int height;
    int width;
    int lava_progression;
    floor *floors;
} map;

void map_info(map*);
map *generate_map(FILE *f, int, int, int);

#endif // MAP