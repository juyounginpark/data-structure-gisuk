/*
    2025202720 박주영
    본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0
int EXIT_COL;
int EXIT_ROW;

typedef struct 
{
    short int row;
    short int col;
    short int dir;
} element;

typedef struct {
    short int vert; // y
    short int horiz; // x 
}offsets; 

offsets move[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

element stack[MAX_STACK_SIZE];
int top = -1;

void path(void);
void push(element);
element pop();

int maze[11][11] = {0};
int mark[11][11] = {0};

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("File open error\n");
        return 1;
    }
    for(int i = 0; i < 11; i++) {
        for(int l = 0; l < 11; l++) {
            maze[i][l] = 1;
        }
    }
    fscanf(fp, "%d %d", &EXIT_ROW, &EXIT_COL);
    for(int i = 1; i <= EXIT_ROW; i++ ) {
        for(int j = 1; j <= EXIT_COL; j++) {
            fscanf(fp, "%d", &maze[i][j]);
        }
    }
    fclose(fp);
    
    path();
    return 0;
}

void push(element item) 
{
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = item;
}

element pop() 
{
    if (top < 0) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

void path(void)
{
    /* output a path through the maze if such a path exists */
    int i, row, col, nextRow, nextCol, dir, found = FALSE;
    element position;
    
    // 초기화
    mark[1][1] = 1;
    position.row = 1;
    position.col = 1;
    position.dir = 0;  // 방향 0부터 시작
    push(position);    // push 사용
    
    while (top > -1 && !found) {
        position = pop();
        row = position.row; 
        col = position.col;
        dir = position.dir;
        
        while (dir < 8 && !found) {
            /* move in direction dir */
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            
            if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
                // 출구 발견 - 현재 위치를 스택에 push
                position.row = row;
                position.col = col;
                position.dir = dir;
                push(position);
                row = nextRow;
                col = nextCol;
                found = TRUE;
            }
            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;
                position.row = row; 
                position.col = col;
                position.dir = dir + 1;
                push(position);
                row = nextRow; 
                col = nextCol; 
                dir = 0;
            }
            else {
                ++dir;
            }
        }
    }
    
    if (found) {
        printf("The path is:\n");
        printf("row  col\n");
        for (i = 0; i <= top; i++)
            printf("%2d%5d\n", stack[i].row, stack[i].col);
        printf("%2d%5d\n", row, col);
    }
    else {
        printf("The maze does not have a path\n");
    }
}