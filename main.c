#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h>
#include <unistd.h>

#include "read_to_array.h"
//#include "bfs.h"

#define MAX_SIZE 1024

int main (int argc, char *argv[]){

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Could not open file: %s\n", argv[1]);
        return 1;
    }

    int height = 0; 
    int width = 0;
    char ch; 

    char buffer[MAX_SIZE];

    while(fgets(buffer, MAX_SIZE, file) != NULL){
        height ++; 
    }

    rewind(file);

    while (ch = fgetc(file) != EOF){
        width++;
    }

    width = (width - height)/height; 


    /*if (mkdir("tmp", 0777) == -1) {
        printf("Could not create a directory!\n");
        return 1; 
    }*/

    //FILE* tmp_file = fopen("tmp_map.txt", "w");

    rewind(file);
    /*
    ch = fgetc(file); 
    while (ch != EOF) 
    { 
        fputc(ch, tmp_file); 
        ch = fgetc(file); 
    }
    */
    //fclose(file);

    //printf("%d - wysokosc, %d - szerokosc \n ", height, width);

    read_to_array(file, height, width);

    //fclose(tmp_file);

    //remove("tmp_map.txt");

    //rmdir("tmp");

    fclose(file);

    return 0; 
}
