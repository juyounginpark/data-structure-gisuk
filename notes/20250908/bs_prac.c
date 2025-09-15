#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void printA(int *arr, int n) {
	for (int i = 0; i < n; i++) printf("%d ", arr[i]);
	puts("");
}

void sort(int arr[], int n) {
	int min;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int l = i + 1; l < n; l++) {
			if (arr[min] > arr[l]) min = l;
		}
		swap(&arr[i], &arr[min]);
	}
}


void main() {
	int arr[] = {2, 4, 1, 5, 3, 444};
	sort(arr, 6);
	printA(arr, 6);
}
