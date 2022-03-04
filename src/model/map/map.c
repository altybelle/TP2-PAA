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

int * getMinimumPathMap(map *m){
    int i,j,c;
    c = 0;
    int *result = (int *) malloc(sizeof(int)*m->height*m->width);
    for (i = m->height-1; i >= 0; i--) {
        for (j = 0; j < m->width; j++) {
            char * stringPart;
            result[(i*m->width)+j] = (int)strtol(m->floors[c].cells[j],&stringPart,10);
            if (strlen(stringPart) != 0){
                result[(i*m->width)+j] = -1;
            } else if (c>0){
                if (j==0){  
                    if (i%2==0){
                        int ganho_vindo_esquerda = result[((i+1)*m->width)+j];
                        printf("[%i,%i] fpE %i\n",i,j, ganho_vindo_esquerda);
                        result[((i)*m->width)+j] += ganho_vindo_esquerda;
                    } else {
                        int ganho_vindo_esquerda = result[((i+1)*m->width)+j];
                        int ganho_vindo_direita =  result[((i+1)*m->width)+j+1];
                        if (ganho_vindo_esquerda >= ganho_vindo_direita && ganho_vindo_esquerda!=-1){
                            printf("[%i,%i] fp0 %i %i\n",i,j, ganho_vindo_esquerda, ganho_vindo_direita);
                            result[((i)*m->width)+j] += ganho_vindo_direita;
                        } else if (ganho_vindo_esquerda!=-1) {
                            printf("[%i,%i] fp1 %i %i\n",i,j, ganho_vindo_esquerda, ganho_vindo_direita);
                            result[((i)*m->width)+j] += ganho_vindo_esquerda;
                        }
                    }
                } else if (j==m->width-1){
                    if (i%2!=0){
                        int ganho_vindo_direita = result[((i+1)*m->width)+j];
                        printf("[%i,%i] 2pE %i\n",i,j, ganho_vindo_direita);
                        result[((i)*m->width)+j] += ganho_vindo_direita;
                    } else {
                        int ganho_vindo_esquerda = result[((i+1)*m->width)+j];
                        int ganho_vindo_direita =  result[((i+1)*m->width)+j+1];
                        if (ganho_vindo_esquerda >= ganho_vindo_direita && ganho_vindo_esquerda!=-1){
                            printf("[%i,%i] 2p0 %i %i\n",i,j, ganho_vindo_esquerda, ganho_vindo_direita);
                            result[((i)*m->width)+j] += ganho_vindo_direita;
                        } else if (ganho_vindo_esquerda!=-1) {
                            printf("[%i,%i] 2p1 %i %i\n",i,j, ganho_vindo_esquerda, ganho_vindo_direita);
                            result[((i)*m->width)+j] += ganho_vindo_esquerda;
                        }
                    }
                } else {
                    int ganho_vindo_esquerda = result[((i+1)*m->width)+j];
                    int ganho_vindo_direita =  result[((i+1)*m->width)+j+1];
                    if (ganho_vindo_esquerda >= ganho_vindo_direita && ganho_vindo_esquerda!=-1){
                        printf("[%i,%i] 3p0 %i %i\n",i,j, ganho_vindo_esquerda, ganho_vindo_direita);
                        result[((i)*m->width)+j] += ganho_vindo_direita;
                    } else if (ganho_vindo_esquerda!=-1) {
                        printf("[%i,%i] 3p1 %i %i\n",i,j,ganho_vindo_esquerda, ganho_vindo_direita);
                        result[((i)*m->width)+j] += ganho_vindo_esquerda;
                    }
                }
            }
        }
        c++;
    }
    for (i = 0; i < m->height; i++) {
        printf("%d. ", i);
        for (j = 0; j < m->width; j++) {
            printf("%i ", result[(i*m->width)+j]);
        }
        puts("");
    }
    return result;
}