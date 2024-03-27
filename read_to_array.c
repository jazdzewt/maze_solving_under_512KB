#include <stdlib.h>
#include <stdio.h> 

void read_to_array (FILE* file, int height, int width ){

    rewind(file);

    int line_to_end = 3;
    int line_to_start = line_to_end - 3;  

    char** array = malloc(3 * sizeof(char*));

    for (int i = 0; i < 3; i++){
        array[i] = malloc(width * sizeof(char));
    }

    for (int i = 0; i< line_to_end; i++){
        for (int j = 0; j< width + 1; j++){
            array[i][j] = (char) fgetc(file); 
        }
    }

    for (int j = 0; j < 3; j++){
        for(int h = 0; h < width; h++){
            printf(" [%c] ", array[j][h]);
        }
        printf("\n");
    }

    //

    for (int i = 0; i < 3; i++){
        free(array[i]);
    }

    free(array); 

}