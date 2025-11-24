#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SIZE = 6;
int DIM;

char **maze;
int **can_host;
int **need_host;
int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void init_maze() {
    DIM = SIZE * 2 + 1;
    
    maze = malloc(DIM * sizeof(char*));
    can_host = malloc(SIZE * sizeof(int*));
    need_host = malloc(SIZE * sizeof(int*));
    
    for (int i = 0; i < DIM; i++)
        maze[i] = malloc(DIM * sizeof(char));
    for (int i = 0; i < SIZE; i++) {
        can_host[i] = malloc(SIZE * sizeof(int));
        need_host[i] = malloc(SIZE * sizeof(int));
    }
    
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            maze[i][j] = (i%2==0 || j%2==0) ? '#' : '.';
    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            can_host[i][j] = 0;
            need_host[i][j] = 1;
        }
}

void free_maze() {
    for (int i = 0; i < DIM; i++)
        free(maze[i]);
    for (int i = 0; i < SIZE; i++) {
        free(can_host[i]);
        free(need_host[i]);
    }
    free(maze);
    free(can_host);
    free(need_host);
}

void generate_maze() {
    srand(time(NULL));
    
    int x = rand() % SIZE;
    int y = rand() % SIZE;
     
    can_host[x][y] = 1;
    need_host[x][y] = 0;
    
    int cnt = 1;
    int host_num = 1;
    
    while (cnt < SIZE * SIZE) {
        int rand_host = rand() % host_num;
        int host_x = -1, host_y = -1;
        
        int current = 0;
        for (int i = 0; i < SIZE && host_x == -1; i++) {
            for (int j = 0; j < SIZE && host_x == -1; j++) {
                if (can_host[i][j] == 1) {
                    if (current == rand_host) {
                        host_x = i;
                        host_y = j;
                    }
                    current++;
                }
            }
        }

        int neighbors[4][2];
        int neighbor_count = 0;
    
        for (int i = 0; i < 4; i++) {
            int nx = host_x + directions[i][0];
            int ny = host_y + directions[i][1];
    
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && need_host[nx][ny] == 1) {
                neighbors[neighbor_count][0] = nx;
                neighbors[neighbor_count][1] = ny;
                neighbor_count++;
            }
        }
        
        if (neighbor_count == 0) {
            can_host[host_x][host_y] = 0;
            host_num--;
            continue;
        }
        
        int random_index = rand() % neighbor_count;
        int selected_x = neighbors[random_index][0];
        int selected_y = neighbors[random_index][1];
        
        can_host[selected_x][selected_y] = 1;
        need_host[selected_x][selected_y] = 0;
        host_num++;
        cnt++;

        int wall_x, wall_y;

        if (host_x == selected_x) {
            wall_x = host_x * 2 + 1;
            wall_y = (host_y < selected_y) ? (host_y * 2 + 2) : (selected_y * 2 + 2);
        } else {
            wall_y = host_y * 2 + 1;
            wall_x = (host_x < selected_x) ? (host_x * 2 + 2) : (selected_x * 2 + 2);
        }

        maze[wall_x][wall_y] = '.';
    }
}

void print_maze() {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++)
            putchar(maze[i][j]);
        putchar('\n');
    }
}

int main() {
    init_maze();
    generate_maze();
    print_maze();
    free_maze();
    return 0;
}
