/*2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.*/   
#include <stdio.h>
#include <stdlib.h>

#define COLS 3
void input2dArray(int ary[][COLS], int rows, int cols) {
    for(int i = 0; i < 2; i++) {
        for(int l = 0; l < 3; l++) {
            scanf("%d", &ary[i][l]);
        }
    }
} // 사용자 데이터 입력
void print2dArray(int ary[][COLS], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int l = 0; l < cols; l++) {
            printf("%d ", ary[i][l]);
        }
        putchar('\n');
    }
} // 행렬 출력

void add(int a[][COLS], int b[][COLS], int c[][COLS], int rows, int cols)
{
    int i, j;
    for( i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            c[i][j] = a[i][j] + b[i][j];
    
}

int main() {
    int a[2][COLS], b[2][COLS], c[2][COLS];
    printf("Input data for 2 x 3 matrix A >> ");
    input2dArray(a, 2, COLS);

    printf("Input data for 2 x 3 matrix B >> ");
    input2dArray(b, 2, COLS);

    printf("matrix A\n");
    print2dArray(a, 2, COLS);

    printf("matrix B\n");
    print2dArray(b, 2, COLS);

    printf("matrix C\n");
    add(a, b, c, 2, 3);
    print2dArray(c, 2, COLS);
    
}

