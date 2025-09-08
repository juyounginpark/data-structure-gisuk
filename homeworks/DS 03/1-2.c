/*
2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/


#define _CRT_SEUCRE_NO_WARNINGS
#include <stdio.h>

float sum(float list[], int n)
{
	float tempsum = 0;
	int i;
	for (i = 0; i < n; i++) {
		tempsum += list[i];
	}
	return tempsum;
}

float rsum(float list[], int n)
{
	if (n) return rsum(list, n - 1) + list[n - 1];
}
int main() {

	float list[10] = { 1,2,3,4,5,6,7,8,9,10 };
	printf("sum: 1에서 10까지의 합은 %f\n", sum(list, 10));
	printf("rsum: 1에서 10까지의 합은 %f\n", rsum(list, 10));
	return 0;
}
