#include <stdio.h>

struct node* new_node (int y, int x);
struct node* next_node (int y, int x, struct node* ptr);
int if_exit(char **maze, int y, int x);
void enqueue(int (*queue)[2], struct node* (*queue_2), int a, int b, struct node* ptr);
int dequeue_a(int (*queue)[2]);
int dequeue_b(int (*queue)[2]);
struct node* dequeue_ptr(struct node* (*queue_2));
void check_surroundings_2(char **maze, int y, int x, struct node* ptr, int (*queue)[2], struct node* (*queue_2));
void bfsv2(char ***maze, int height, int width, FILE* file, int module_num);