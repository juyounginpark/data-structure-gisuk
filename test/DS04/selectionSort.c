#include "selectionSort.h"

void sort(int a[], int n)
{
    int i, j, min, temp;
    for(i = 0; i < n - 1; i++) {
        min = i;
        for(j = i + 1; j < n; j++) {
            if(a[j] < a[min]) {
                min = j;
            }
        }
        SWAP(a[i], a[min], temp);
    }
}