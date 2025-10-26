#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

#define MAX_SIZE 100

void sort(int[], int);
int binsearch(int list[], int searchnum, int left, int right);

int main() {
	int i, n, seed, searchnum, result;
	int list[MAX_SIZE];

	printf("input seed >> ");
	scanf("%d", &seed);
	printf("Enter the number of numbers to generate >> ");
	scanf("%d", &n);

	srand(seed);
	puts("Random numbers:");
	for (i = 0; i < n; i++) {
		list[i] = rand() % 1000;
		printf("%d ", list[i]);
	}
	puts("");

	sort(list, n);

	puts("Sorted array:");
	for(i = 0; i < n; i++) printf("%d ", list[i]);
	puts("");

	printf("Enter the number to search >> ");
	scanf("%d", &searchnum);

	result = binsearch(list, searchnum, 0, n - 1);

	if (result != -1) {
		printf("The search number is present in list[%d]\n", result);
	}
	else {
		puts("The search number is not present");
	}

	return 0;
}

void sort(int list[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for(j = i + 1; j < n; j++) {
			if(list[j] < list[min]) {
				min = j;
			}
		}
		SWAP(list[i], list[min], temp);
	}
}

int binsearch(int list[], int searchnum, int left, int right) {
	int middle;
	if(left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum))
		{
		case -1:
			return binsearch(list, searchnum, middle + 1, right);	
		case 0:
			return middle;
		case 1:
			return binsearch(list, searchnum, left, middle - 1);
		}
	}
	return -1;
}