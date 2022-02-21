#include "map.h"

#include <string.h>

map *generate_map(FILE *f, int height, int width, int lava_progression) {
    int i, j;
    map *gen = (map*) malloc(sizeof(map));

    gen->height = height;
    gen->width = width;
    gen->lava_progression = lava_progression;

    gen->floors = (floor*) malloc(sizeof(floor) * height);

    for (i = 0; i < height; i++) {
        int floor_number = height - i - 1;
        gen->floors[floor_number].id = floor_number;
        gen->floors[floor_number].cells = (char**) malloc(sizeof(char*) * width);
        for (j = 0; j < width; j++) {
            char content[3];
            fscanf(f, "%s\n", content);
            gen->floors[floor_number].cells[j] = (char*) malloc(sizeof(char) * MAX_CHAR);
            strcpy(gen->floors[floor_number].cells[j], content);
        }
    }

    return gen;
}

void map_info(map *m) {
    int i, j;
    printf("Altura: %d\n", m->height);
    printf("Largura: %d\n", m->width);
    printf("Avanco da lava: %d\n", m->lava_progression);
    puts("Niveis: ");
    for (i = 0; i < m->height; i++) {
        printf("%d. ", i);
        for (j = 0; j < m->width; j++) {
            printf("%s ", m->floors[i].cells[j]);
        }
        puts("");
    }
}