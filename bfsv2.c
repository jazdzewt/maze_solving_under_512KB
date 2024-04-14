#include <stdlib.h>
#include <stdio.h>

#define QUEUE_MAX_SIZE 100

typedef struct node {
    int x; 
    int y; 
    struct node* previous; 
} node; 

struct node* new_node (int y, int x){

    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    new_node->x = x;
    new_node->y = y; 
    new_node->previous = NULL;
    return new_node;
}

struct node* next_node (int y, int x, struct node* ptr){

    struct node *next_node = (struct node*)malloc(sizeof(struct node));
    if (next_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    next_node->y = y;
    next_node->x = x;
    next_node->previous = ptr;
    return next_node;
}

void enqueue(int (*queue)[2], struct node* (*queue_2), int a, int b, struct node* ptr) {
    int i = 0;

    while(queue[i][0] != 0 && i < QUEUE_MAX_SIZE){
        i++;
    }
    if(i < QUEUE_MAX_SIZE){
        queue[i][0] = a; 
        queue[i][1] = b;
    }

    queue_2[i] = ptr; 
}

int dequeue_a(int (*queue)[2]) {
    int a = queue[0][0];
    return a;
}

int dequeue_b(int (*queue)[2]) {
    int b = queue[0][1];
    int i = 1; 
    while (queue[i][0] != 0 && i < QUEUE_MAX_SIZE) {
        queue[i-1][0] = queue[i][0]; 
        queue[i-1][1] = queue[i][1];        
        i++;
    }
    queue[i-1][0] = 0;
    queue[i-1][1] = 0;
    return b; 
}

struct node* dequeue_ptr(struct node* (*queue_2)){

    struct node* ptr = queue_2[0];

    int i = 1; 
    while (queue_2[i] != NULL && i < QUEUE_MAX_SIZE - 1){
        queue_2[i-1] = queue_2[i];
        i++;
    }
    return ptr; 
}

void check_surroundings_2(char **maze, int y, int x, struct node* ptr, int (*queue)[2], struct node* (*queue_2)) {
    //maze[y][x] = 'O';

    struct node* next_ptr = NULL;

    if(maze[y][x+1] == ' '){
        maze[y][x+1] = 'O';
        next_ptr = next_node(y, x+1, ptr);
        enqueue(queue, queue_2, y, x+1, next_ptr);
    }
    
    if(maze[y+1][x] == ' '){
        maze[y+1][x] = 'O';
        next_ptr = next_node(y+1, x, ptr);
        enqueue(queue, queue_2, y+1, x, next_ptr);
    }
    
    if(maze[y][x-1] == ' '){
        maze[y][x-1] = 'O';
        next_ptr = next_node(y, x-1, ptr);
        enqueue(queue, queue_2, y, x-1, next_ptr);
    }
    
    if(maze[y-1][x] == ' '){
        maze[y-1][x] = 'O';
        next_ptr = next_node(y-1, x, ptr);
        enqueue(queue, queue_2, y-1, x, next_ptr);
    }
}

void clear_queue (int (*queue)[2], struct node* (*queue_2)){

    struct node* ptr;
    struct node* tmp_ptr; 

    for(int i = 0; i<QUEUE_MAX_SIZE; i++){
 
        queue[i][0] = 0; 
        queue[i][1] = 0;

        if(queue_2[i] != NULL){
            ptr = queue_2[i]; 
            while(ptr->previous == NULL){
                tmp_ptr = ptr->previous; 
                free(ptr);
                ptr = tmp_ptr;
            }
        }
        queue_2[i] = NULL;
    }
}

int exit_count (char **maze, int y, int x){
    int i = 0;  

    if(maze[y-1][x] == 'Z'){
        i ++;
    }
    if(maze[y+1][x] == 'Z'){
        i ++;
    }
    if(maze[y][x-1] == 'Z'){
        i ++;
    }
    if(maze[y][x+1] == 'Z'){
        i ++;
    }

    return i; 
}

void bfsv2(char ***maze, int height, int width, FILE* file, int module_num) { 

    int (*queue)[2] = malloc(QUEUE_MAX_SIZE * sizeof(*queue));


    struct node **queue_2;

    queue_2 = malloc(QUEUE_MAX_SIZE * sizeof(struct node *));

    for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
        queue_2[i] = malloc(sizeof(struct node));
        queue_2[i] = NULL; 
    }
    
    int px = -1;
    int py = -1; 

    int kx = -1; 
    int ky = -1; 

    //szukanie p i k
    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if ((*maze)[i][j] == 'P'){
                px = j; 
                py = i;
                fprintf(file, "P%d,%d\n", py, px); 
            }
            if ((*maze)[i][j] == 'K'){
                kx = j; 
                ky = i; 
                fprintf(file, "K%d,%d\n", ky, kx); 
            }
        }
    } 

    struct node* struct_ptr;

    int i, j, x, y = 0;
    int h = 0;
    int path_step = 0; 
    

    //bfs dla modułu z p i k 
    if(px != -1 && kx != -1){
    
        struct_ptr = new_node(ky, kx - 1); 

        enqueue(queue, queue_2, ky, kx, struct_ptr);

        while(h == 0){

            if (j == px + 1){
                if(i == py){
                    h = 1; 
                    break; 
                }
            }

            i = dequeue_a(queue);
            j = dequeue_b(queue);
            struct_ptr = dequeue_ptr(queue_2);
            check_surroundings_2(*maze, i, j, struct_ptr, queue, queue_2);        
        }

        //int x, y;
    
        while (struct_ptr->previous != NULL){
            y = struct_ptr->y; 
            x = struct_ptr->x;
            fprintf(file, "%d,%d\n", y, x);

            struct_ptr = struct_ptr->previous;
        } 
    //bfs dla modułu z p
    }else if(px != -1 && kx == -1){

        for(int g = 1; g < width-1; g++){ 

            if((*maze)[height][g] == 'Z' && (*maze)[height-1][g] == ' '){
                
                (*maze)[height-1][g] = 'O';

                struct_ptr = new_node(height-1, g);

                enqueue(queue, queue_2, height-1, g, struct_ptr);
                
                while(h == 0){

                    if (j == px + 1){
                        if(i == py){
                            h = 1; 
                            break; 
                        }
                    }    

                    if(queue[0][0] == 0 && queue[0][1] == 0){
                        if(exit_count((*maze), i, j) != 0){
                            h = 1; 
                            break;
                        }
                    }

                    i = dequeue_a(queue);                    
                    j = dequeue_b(queue);                    
                    struct_ptr = dequeue_ptr(queue_2);                    
                    check_surroundings_2((*maze), i, j, struct_ptr, queue, queue_2);
                }
                
                printf("i, j - %d, %d", i, j);
                
                //wypisywanie do pliku 
                fprintf(file, "#%d#%d,%d\n",module_num, height, g);

                path_step = 0; 
                while (struct_ptr->previous != NULL){
                    y = struct_ptr->y; 
                    x = struct_ptr->x;
                    fprintf(file, "%d,%d\n", y, x);
                    path_step++;
                    struct_ptr = struct_ptr->previous;
                }

                //wypisywanie dlugosci sciezki dla modulu
                fprintf(file, "L%d\n", path_step);

                //czyszczenie mapy 
                for (int i = 0; i < height; i++){
                    for (int j = 0; j < width; j++){
                        if ((*maze)[i][j] == 'O'){
                            (*maze)[i][j] = ' '; 
                        }
                    }
                }

                //czyszczenie pamieci i zerowanie zmiennych
                clear_queue(queue, queue_2);
                
                h = 0;
                i = -1; 
                j = -1; 
            }
        }
    //bfs dla modułu z k 
    }else if(kx != -1 && px == -1){

        for(int g = 0; g<width-1; g++){
            if(*maze[0][g] == ' '){

                struct_ptr = new_node(ky, kx);

                enqueue(queue, queue_2, height-1, g, struct_ptr);

                while(i != 0){

                    path_step++; 

                    i = dequeue_a(queue);
                    j = dequeue_b(queue);
                    struct_ptr = dequeue_ptr(queue_2);
                    check_surroundings_2(*maze, i, j, struct_ptr, queue, queue_2);        
                }
                //int x, y;

                fprintf(file, "#%d#%d#%d\n",module_num, g, path_step);

                while (struct_ptr->previous != NULL){
                    y = struct_ptr->y; 
                    x = struct_ptr->x;
                    fprintf(file, "%d,%d\n", y, x);

                    struct_ptr = struct_ptr->previous;
                }

                *maze[0][j] == 'X';

                for (int i = 0; i < height; i++){
                    for (int j = 0; j < width; j++){
                        if (*maze[i][j] == 'O'){
                            *maze[i][j] = ' '; 
                        }
                    }
                }
            }
        }
    //bfs dla modułu bez p i k 
    } else {
        for(int g = 0; g<width-1; g++){
            if(*maze[height-1][g] == ' '){

                *maze[height-1][g] = 'O';

                struct_ptr = new_node(height-1, g);

                enqueue(queue, queue_2, height-1, g, struct_ptr);

                while(i != 0/*i != py && j != (px + 1)*/){

                   
                    i = dequeue_a(queue);                   
                    j = dequeue_b(queue);                    
                    struct_ptr = dequeue_ptr(queue_2);                     
                    check_surroundings_2(*maze, i, j, struct_ptr, queue, queue_2);        
                }

                fprintf(file, "#%d#%d#%d\n",module_num, g, path_step);

                while (struct_ptr->previous != NULL){
                    y = struct_ptr->y; 
                    x = struct_ptr->x;
                    fprintf(file, "%d,%d\n", y, x);

                    struct_ptr = struct_ptr->previous;
                }

                *maze[0][j] == 'X';

                for (int i = 0; i < height; i++){
                    for (int j = 0; j < width; j++){
                        if (*maze[i][j] == 'O'){
                            *maze[i][j] = ' '; 
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
        free(queue_2[i]);
    }
    
    free(queue_2);

    free(queue);
}
