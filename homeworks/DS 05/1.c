/*2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.*/

#include <stdio.h>
#include <stdlib.h>
int sumAry2D_f1(int ary[][3], int row, int col) {
	int res = 0;
	for(int i = 0; i < row; i++) {
		for(int l = 0; l < col; l++) {
			res += ary[i][l];
		}
	}
	return res;
}

int sumAry2D_f2(int (*ary)[3], int row, int col) {
	int res = 0;
    for(int i = 0; i < row; i++) {
        for(int l = 0; l < col; l++) {
            res += ary[i][l];
        }
    }
    return res;
}

int sumAry2D_f3(int ary[2][3], int row, int col) {
	int res = 0;
    for(int i = 0; i < row; i++) {
        for(int l = 0; l < col; l++) {
            res += ary[i][l];
        }
    }
    return res;
}

int sumAry2D_f4(int **ary, int row, int col) {
	int res = 0;
    for(int i = 0; i < row; i++) {
        for(int l = 0; l < col; l++) {
            res += ary[i][l];
        }
    }
    return res;
}

int sumAry2D_f5(int ***ary, int row, int col) {
	int res = 0;
    for(int i = 0; i < row; i++) {
        for(int l = 0; l < col; l++) {
            res += (*ary)[i][l];
        }
    }
    return res;
}
void freeAry2D(int **ary, int row) {
	for(int i = 0; i < row; i++) free(ary[i]);
	printf("2D array - free!!\n");
	free(ary);
}

int main(void)
{
	// 정적 할당의 2차원 배열(2행3열)
	int ary2D[2][3]= { {1, 2, 3}, {4, 5, 6}};
	// 동적 할당의 2차원 배열(2행3열)
	int r, c;
	int **ary = (int **) malloc(sizeof(int*) * 2);
	for ( r = 0; r < 2; r++)
		ary[r] = (int *) malloc( sizeof(int) * 3);
	for ( r = 0; r < 2; r++)
		for ( c = 0; c < 3; c++)
			ary[r][c] = r+c;
	// 정적 할당 배열
	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, 2, 3)); // 배열 파라미터(권장)
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary2D, 2, 3)); // 배열 포인터
	printf("sumAry2D_f3() %d\n", sumAry2D_f3(ary2D, 2, 3));
	// 동적 할당 배열
	printf("sumAry2D_f4() %d\n", sumAry2D_f4(ary, 2, 3));
	printf("sumAry2D_f5() %d\n", sumAry2D_f5(&ary, 2, 3));
	// 동적 할당 배열을 sumAry2D_f1, f2, f3로 전달할 수 있을까? 테스트해보라!
	//printf("sumAry2D_f1~f3() %d\n", sumAry2D_f1(ary, 2, 3));
	// 정적 할당 배열을 sumAry2D_f4, f5로 전달할 수 있을까? 테스트해보라!
	//printf("sumAry2D_f4~f5() %d\n", sumAry2D_f4(ary2D, 2, 3));
	freeAry2D(ary, 2); // 동적 할당 배열의 메모리 해제
	return 0;
}
