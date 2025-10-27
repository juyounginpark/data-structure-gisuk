/*
2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define COMPARE(x, y) (((x) < (y)) ? -1: ((x) == (y)) ? 0: 1)

void printArr(int list[], int n) {
    for(int i = 0; i < n; i++) printf("%d ", list[i]);
    putchar('\n');
}

void sort(int list[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (list[j] < list[min]) {
                min = j;
            }
        }
        SWAP(list[i], list[min], temp);
    }
}

int binsearch(int list[], int left, int right, int num) {
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], num))
		{
		case -1:
			left = middle + 1;
			break;
		case 0:
			return middle;
		case 1:
			right = middle - 1;
			break;
		}
	}
	return -1;
}

int main() {
	int seed, n;
	printf("input seed >> ");
	scanf("%d", &seed);
	printf("Enter the number of numbers to generate >> ");
	scanf("%d", &n);
	puts("\n");
	srand(seed);

	int arr[100];
	
	printf("Random numbers:\n");
	for(int i = 0; i < n; i++) {
		arr[i] = rand()%1000;
		printf("%d ", arr[i]);
	}
	puts("\n");
	
	printf("Sorted array:\n");
	sort(arr, n);
	printArr(arr, n);
	putchar('\n');

	int snum;
	printf("Enter the number to search >> ");
	scanf("%d", &snum);

	int res = binsearch(arr, 0, n-1, snum);
	if(res == -1) {
		puts("The search number is not present");
		return 0;
	}
	printf("The search number is present in list[%d]\n", res);
	
	return 0;
}