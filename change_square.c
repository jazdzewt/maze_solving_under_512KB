#include <stdlib.h> 
#include <stdio.h>

int change_square (char ***array, int lenght){
    int change_sum; 

    change_sum = 0; 

    for(int i=0; i <= lenght; i++){
        if(wall_count(*array, i) >= 3){
            (*array)[1][i] = "X";
            change_sum++;  
        }
    }

    return change_sum; 
}