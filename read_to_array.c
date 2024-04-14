#include <stdlib.h>
#include <stdio.h> 

#include "zalewanie.h"
#include "bfsv2.h"

#define MAX_MODULE_SIZE 50 

void read_to_array (FILE* file, int height, int width ){

    FILE* tmp_file = fopen("tmp_path.txt", "w");

    int module_vol = (height + MAX_MODULE_SIZE - 1) / MAX_MODULE_SIZE;

    int module_number = 1; 
    
    rewind(file); 

    char** array = malloc((MAX_MODULE_SIZE) * sizeof(char*));

    for (int i = 0; i <= MAX_MODULE_SIZE; i++){
        array[i] = malloc(width * sizeof(char));
    }

    for (int i = 0; i<= MAX_MODULE_SIZE; i++){
        for (int j = 0; j< width  + 1; j++){
            array[i][j] = (char) fgetc(file); 
        }
    }
    
    for(int i = 0; i < width; i++){
        if(array[MAX_MODULE_SIZE][i] == ' '){
            array[MAX_MODULE_SIZE][i] = 'Z';
        }
    }

    //
    while(zalewanie(&array, MAX_MODULE_SIZE+1, width));

    //printowanie mapy 
    for (int j = 0; j <= MAX_MODULE_SIZE; j++){
        for(int h = 0; h < width; h++){
            printf("%c", array[j][h]);
        }
        printf("\n");
    }

    printf("\n");

    bfsv2(&array, MAX_MODULE_SIZE, width, tmp_file, module_number);


    //printowanie mapy 
    for (int j = 0; j <= MAX_MODULE_SIZE; j++){
        for(int h = 0; h < width; h++){
            printf("%c", array[j][h]);
        }
        printf("\n");
    }
    /*
    for (int i = 2; i <= module_vol; i++){
        module_number = i; 

        for(int j = 0; j < width; j++){
            array[0][j] = array[MAX_MODULE_SIZE -2][j];
        }

        for (int i = 0; i< MAX_MODULE_SIZE; i++){
            for (int j = 0; j< width  + 1; j++){
                array[i][j] = (char) fgetc(file); 
            }
        }
        for(int i = 0; i < width; i++){
            array[MAX_MODULE_SIZE][i] = 'Z';
        }
        
        while(zalewanie(&array, MAX_MODULE_SIZE, width));
        bfsv2(&array, MAX_MODULE_SIZE, width, tmp_file, module_number);
    }
    */

    for (int i = 0; i <= MAX_MODULE_SIZE; i++){
        free(array[i]);
    }
    
    free(array); 
}
