/* 1.c */
/* 학번 이름 */
/* 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다. */

#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101 /* 0이 아닌 항의 최대 개수 + 1 [cite: 819] */
#define MAX_COLS 50   /* 최대 열의 크기 (임의 지정) */

/* 희소행렬의 항 구조체 [cite: 821-825] */
typedef struct {
    int row;
    int col;
    int value;
} term;

term a[MAX_TERMS]; /* 원본 희소행렬 [cite: 827] */
term b[MAX_TERMS]; /* 전치된 희소행렬 [cite: 827] */

/**
 * @brief Program 2.9: 희소행렬의 빠른 전치 함수 [cite: 881-904]
 * a의 전치행렬을 b에 저장합니다.
 */
void fastTranspose(term a[], term b[])
{
    /* rowTerms: a의 열별 빈도수 저장, startingPos: b의 행별 시작위치 저장 */
    int rowTerms[MAX_COLS], startingPos[MAX_COLS];
    int i, j, numCols = a[0].col, numTerms = a[0].value;

    b[0].row = numCols; b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0) { /* 0이 아닌 행렬일 경우 */
        
        /* 1. rowTerms 계산 (a의 열 빈도수) [cite: 829] */
        for (i = 0; i < numCols; i++)
            rowTerms[i] = 0;
        for (i = 1; i <= numTerms; i++)
            rowTerms[a[i].col]++;

        /* 2. startingPos 계산 (b의 행 시작위치) [cite: 830] */
        startingPos[0] = 1;
        for (i = 1; i < numCols; i++)
            startingPos[i] = startingPos[i-1] + rowTerms[i-1];

        /* 3. a(i,j) -> b(j,i) 수행 [cite: 830] */
        for (i = 1; i <= numTerms; i++) {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

/**
 * @brief 희소행렬(term)을 2차원 배열(dense) 형태로 출력 [cite: 905-906]
 */
void printMatrix(term matrix[])
{
    int rows = matrix[0].row;
    int cols = matrix[0].col;
    int numTerms = matrix[0].value;
    int i, j, k;

    /* 2차원 배열을 0으로 초기화 */
    int dense[50][50] = {0}; // 최대 크기를 50x50으로 가정
    
    /* 희소행렬의 항들을 2차원 배열에 배치 */
    for (k = 1; k <= numTerms; k++) {
        dense[matrix[k].row][matrix[k].col] = matrix[k].value;
    }

    /* 2차원 배열 출력 */
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%5d", dense[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    FILE *fp_in, *fp_out;
    int i;

    /* 1. "a.txt" 파일 열기 */
    if (!(fp_in = fopen("a.txt", "r"))) {
        fprintf(stderr, "Cannot open file a.txt\n");
        exit(EXIT_FAILURE);
    }

    /* 2. "a.txt"에서 희소행렬 a 읽기 */
    fscanf(fp_in, "%d %d %d", &a[0].row, &a[0].col, &a[0].value);
    for (i = 1; i <= a[0].value; i++) {
        fscanf(fp_in, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
    }
    fclose(fp_in);

    /* 3. 행렬 A 출력 */
    printf("A\n");
    printMatrix(a);

    /* 4. 빠른 전치 수행 */
    fastTranspose(a, b);

    /* 5. 행렬 B (전치 결과) 출력 */
    printf("\nB\n");
    printMatrix(b);

    /* 6. "b.txt" 파일 열기  */
    if (!(fp_out = fopen("b.txt", "w"))) {
        fprintf(stderr, "Cannot open file b.txt\n");
        exit(EXIT_FAILURE);
    }

    /* 7. "b.txt"에 희소행렬 b 쓰기 */
    fprintf(fp_out, "%d %d %d\n", b[0].row, b[0].col, b[0].value);
    for (i = 1; i <= b[0].value; i++) {
        fprintf(fp_out, "%d %d %d\n", b[i].row, b[i].col, b[i].value);
    }
    fclose(fp_out);

    return 0;
}