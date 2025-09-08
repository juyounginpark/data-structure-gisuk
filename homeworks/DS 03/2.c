/*
2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#define MAX_SIZE 4
int count;
void add(int a[][MAX_SIZE], int b[][MAX_SIZE], int c[][MAX_SIZE], int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		count++;
		for(j=0; j<cols; j++) {
			count++;
			c[i][j] = a[i][j] + b[i][j];
			count++;
		}
		count++;
	}
	count ++;

}
int main() {
	int a[3][4];
	int b[3][4];
	int c[3][4];
	FILE* fpA = fopen("a.txt", "r");
	
	for(int i=0; i<3; i++) {
		for(int l=0; l< MAX_SIZE; l++) {
			fscanf(fpA, "%d", &a[i][l]);
		}
	}
	
	add(a, b, c, 3, 4);
	fclose(fpA);
	
	printf("step count : %d", count);
	
}
