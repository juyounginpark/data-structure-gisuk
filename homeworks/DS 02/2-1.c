#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}


void printArr(int list[], int n) {
    for(int i = 0; i < n; i++) printf("%d ", list[i]);
    putchar('\n');
}

int compare(int x, int y) {
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}

void sort(int list[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (list[j] < list[min]) {
                min = j;
            }
            swap(&list[i], &list[min]);
        }
    }
}

int binsearch(int list[], int left, int right, int num) {
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (compare(list[middle], num))
		{
		case -1:
			left = middle + 1;
			break;
		case 0 :
			return middle;
		case 1 : right = middle - 1;

		}
	}
	return -1;

}
void main() {
	int seed, n;
	printf("input seed >> ");
	scanf("%d", &seed);
	printf("Enter the number of numbers to generate >> ");
	scanf("%d", &n);
	puts("\n");
	srand(seed);

	int arr[101];
	
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

	int res = binsearch(arr, 0, n-1,snum);
	if(res == -1) {
		puts("The search number is not present");
		return;
	}
	printf("The search number is present in list[%d]\n",res );

}

