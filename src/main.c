#include <stdio.h>
#include <stdlib.h>

#include "model/map/map.h"

int start(FILE*);

int main() {
    FILE *f = NULL;
    char file_path[250];

    do {

        printf("Insira o caminho do arquivo a ser lido: ");
        scanf("%s", file_path);

        f = fopen(file_path, "r");

        if (!f) {
            puts("Arquivo nao foi encontrado.");
        } else {
            start(f);
        }

    } while (file_path[0] != '0');
}

int start(FILE *f) {
    int height, width, time_wasted, lava_progression;
    fscanf(f, "%d %d %d %d", &height, &width, &time_wasted, &lava_progression);
    map m = *generate_map(f, height, width, lava_progression);
    map_info(&m);
    getMinimumPathMap(&m);
    return 0;
}