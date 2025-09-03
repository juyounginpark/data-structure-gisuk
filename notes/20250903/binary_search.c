#include <stdio.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void printArr(int list[], int left, int right) {
    for(int i = left; i <= right; i++) printf("%d ", list[i]);
    putchar('\n');
}

void sort(int list[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n-1; i++) {
void printArr(int list[], int left, int right) {
    for(int i = left; i <= right; i++) printf("%d ", list[i]);
    putchar('\n');
}
        min = i;
        for (j = i + 1; j < n; j++) {
            if (list[j] < list[min]) {
                min = j;
            }
            SWAP(list[i], list[min], temp);
        }
    }
}

char* bsearch(int list[], int left, int right, int num) {
	printArr(list, left, right);
	int middle = (left + right) / 2;
	if (middle < left) return "no";
	if(num < list[middle]) right = middle - 1;
	else if (num == list[middle]) return "yes";
	else left = middle + 1;
	
	bsearch(list, left, right, num);


}

void main() {
	int n = 5;
	int arr[] = { 1, 5, 2, 4, 100};
	sort(arr, n);
	puts(bsearch(arr, 0, n-1, 100));

}
