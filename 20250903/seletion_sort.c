#include <stdio.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void sort(int list[], int n) {
	int i, j, min, temp;
	for (i = 0; i < n-1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[min]) {
				min = j;
			}
			SWAP(list[i], list[min], temp);
		}
	}
}

void printArr(int list[], int n) {
	for(int i = 0; i < n; i++) printf("%d\n", list[i]);
}

void main() {
	int arr[] = { 1, 4, 5, 3, 2 };
	sort(arr, 5);
	printArr(arr, 5);
	
}
