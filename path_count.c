#include <stdlib.h>
#include <stdio.h> 

int path_count (char **array, int x){
    int sum; 

    if (array[1][x-1] == " " && array[2][x] == " "){
        sum++; 
    }
    if (array[1][x+1] == " " && array[2][x] == " "){
        sum++; 
    }
    if (array[1][x-1] == " " && array[0][x] == " "){
        sum++; 
    }
    if (array[1][x+1] == " " && array[0][x] == " "){
        sum++; 
    }

    return sum; 
}