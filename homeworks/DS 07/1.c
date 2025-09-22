/*
	2025002720 박주영
	본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#define MAX_TERMS 101
#define MAX_COL 101
// 희소행렬의 0아닌 항
typedef struct
{
	int row;
	int col;
	int value;
}term;
// 희소행렬 a, b
term a[MAX_TERMS]; // a[0] : 행 크기, 열 크기, 0아닌 항의 개수
term b[MAX_TERMS]; // a의 전치행렬 b

void fastTranspose(term a[], term b[])
{
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols; b[0].col = a[0].row;
	b[0].value = numTerms;
	if (numTerms > 0) {
		for (i = 0; i < numCols; i++)
			rowTerms[i] = 0;
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		startingPos[0] = 1;
		for (i = 1; i <= numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col; b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

void printMaxtrix(term matrix[]) {
	
	int i, l;
	int arr[MAX_COL][MAX_TERMS];
	for(i = 0; i < matrix[0].col; i++) {
		for(l = 0; l < matrix[0].row; l++) {
			arr[i][l] = 0;
		}
	}

	for(int i = 1; i <= matrix[0].value; i++) {
		arr[matrix[i].row][matrix[i].col] = matrix[i].value;
	}

	for(i = 0; i < matrix[0].row; i++) {
		for(l = 0; l < matrix[0].col; l++) {
			printf("%4d", arr[i][l]);
		}
		puts("");
	}
}

int main() {
		FILE *fp;
		fp = fopen("a.txt", "r");
		fscanf(fp, "%d %d %d", &a[0].row, &a[0].col, &a[0].value);
		for(int i = 1; i <= a[0].value; i++) {
			fscanf(fp, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
		}
		fastTranspose(a, b);
		puts("A");
		printMaxtrix(a);

		puts("B");
		printMaxtrix(b);

		fclose(fp);

		FILE *out;
		out = fopen("b.txt", "w+");
		for(int i = 0; i <= b[0].value; i++) {
			fprintf(fp, "%d %d %d\n", b[i].row, b[i].col, b[i].value);
		}

}
