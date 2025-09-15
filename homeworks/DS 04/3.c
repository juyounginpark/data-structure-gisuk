/*2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.*/   
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) \
    if(!((p) = malloc(s))) {\
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);\
    }


int** make2dArray(int rows, int cols)
{
    int **ary, i;
    MALLOC(ary, rows * sizeof( *ary)); // 매크로 함수 MALLOC을 사용
    for( i = 0; i < rows; i++)
        MALLOC (ary[i], cols * sizeof( **ary));
    return ary;
}

void inputMatrix(int **ary, int rows, int cols) {
	
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			scanf("%d", &ary[r][c]); 

} // 사용자 데이터 입력
void printMatrix(int **ary, int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%d", ary[r][c]); 
        }
		putchar('\n');
    }		
} // 행렬 출력

void addMatrix(int **a, int **b, int **c, int rows, int cols)
{
    int i, j;
    for( i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            c[i][j] = a[i][j] + b[i][j];
}

void free2dArray(int **ary, int rows) {
    for(int i = 0; i < rows; i++) {
        free(ary[i]);
    }
    free(ary);
}

int main() {
    int **a, **b, **c;
    int n, m;
    printf("Enter row size and column size (ex) 2 3 >> ");
    scanf("%d %d", &n, &m);

    a = make2dArray(n, m);
    b = make2dArray(n, m);
    c = make2dArray(n, m);
    printf("Input data for 2 x 3 matrix A >> ");
    inputMatrix(a, n, m);

    printf("Input data for 2 x 3 matrix B >> ");
    inputMatrix(b, n, m);

    printf("matrix A\n");
    printMatrix(a, n, m);

    printf("matrix B\n");
    printMatrix(b, n, m);

    printf("matrix C\n");
    addMatrix(a, b, c, n, m);
    printMatrix(c, n, m);
    free2dArray(a, m);
    free2dArray(b, m);
    free2dArray(c, m);
    printf("2D array - free!!\n");
}
