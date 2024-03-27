#include <stdlib.h>
#include <stdio.h> 

int wall_count (char **array, int x){
    int sum; 

    if (array[0][x] == "X"){
        sum++; 
    }
    if (array[2][x] == "X"){
        sum++; 
    }
    if (array[0][x-1] == "X"){
        sum++; 
    }
    if (array[0][x+1] == "X"){
        sum++; 
    }

    return sum; 
}