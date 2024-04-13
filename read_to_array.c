#include <stdlib.h>
#include <stdio.h> 

#include "zalewanie.h"
#include "bfsv2.h"

#define MAX_MODULE_SIZE 70 

void read_to_array (FILE* file, int height, int width ){

    FILE* tmp_file = fopen("tmp_map.txt", "w");

    int module_number = 1; 

    rewind(file); 

    char** array = malloc(MAX_MODULE_SIZE * sizeof(char*));

    for (int i = 0; i < MAX_MODULE_SIZE; i++){
        array[i] = malloc(width * sizeof(char));
    }

    for (int i = 0; i< MAX_MODULE_SIZE; i++){
        for (int j = 0; j< width  + 1; j++){
            array[i][j] = (char) fgetc(file); 
        }
    }

    //
    while(zalewanie(&array, MAX_MODULE_SIZE, width));

    //printowanie mapy 
    for (int j = 0; j < MAX_MODULE_SIZE; j++){
        for(int h = 0; h < width; h++){
            printf(" [%c] ", array[j][h]);
        }
        printf("\n");
    }

    bfsv2(&array, MAX_MODULE_SIZE, width, tmp_file, module_number);

    //szukanie konca 
    /*
    int kx = 0; 
    int ky = 0; 

    for (int i = 0; i< 50; i++){
        for (int j = 0; j< width + 1; j++){
             if (array[i][j] == 'K'){
                kx = j; 
                ky = i; 
             }
        }
    }

    printf("kx: %d ky: %d\n", kx, ky);
 

    //bfs jesli koniec 
    if (kx != 0 && ky != 0){

    }
    */

    //printowanie mapy 
    for (int j = 0; j < MAX_MODULE_SIZE; j++){
        for(int h = 0; h < width; h++){
            printf(" [%c] ", array[j][h]);
        }
        printf("\n");
    }

    //

    for (int i = 0; i < MAX_MODULE_SIZE; i++){
        free(array[i]);
    }

    free(array); 

}
