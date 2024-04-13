#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char check_surroundings(char **maze, int x, int y, int width, int height) {
    char sum = 0;

    if (x + 1 < width && maze[y][x + 1] == 'X')
        sum++;

    if (y + 1 < height && maze[y + 1][x] == 'X')
        sum++;

    if (y - 1 >= 0 && maze[y - 1][x] == 'X')
        sum++;

    if (x - 1 >= 0 && maze[y][x - 1] == 'X')
        sum++;

    return sum;
}



bool zalewanie(char ***maze, int height, int width) {
    bool found = false;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((*maze)[i][j] == ' ' && check_surroundings(*maze, j, i, width, height) >= 3){
                (*maze)[i][j] = 'X';
                found = true;
            }            
        }
    }
    return found;
}
