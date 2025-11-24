/*
    2025002720 박주영
    본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
    int key;
} element;

int call_count = 0;
int n;
void quickSort(element a[], int left, int right) {
    call_count++;
    int pivot, i, j;
    element temp;
    for(int i = 1; i <= n; i++) printf("%4d ",a[i].key);
    printf(":%4d%4d\n",left, right);
    if (left < right) {
        i = left;
        j = right + 1;
        pivot = a[left].key;

        do {
            do { i++; } while (a[i].key < pivot);
            do { j--; } while (a[j].key > pivot);
            if (i < j) SWAP(a[i], a[j], temp);
        } while (i < j);

        SWAP(a[left], a[j], temp);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    FILE * out_fp = fopen("output.txt", "w+");
    element a[MAX_SIZE];
    int i;

    if (fp == NULL) return -1;

    fscanf(fp, "%d", &n);
    for (i = 1; i <= n; i++) {
        fscanf(fp, "%d", &a[i].key);
    }
    a[n + 1].key = 2147483647; 

    printf("<<<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>>>>\n");
    for (i = 1; i <= n; i++) printf("%d ", a[i].key);
    printf("\n\n");
    
    puts("execution of quick sort ...");
    for(int i = 0; i < n; i++) printf("[%2d] ",i+1);
    puts("[left right]");
    quickSort(a, 1, n);

    printf("calls of quick sort:%4d\n\n", call_count);
    printf("<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>>\n");
    for (i = 1; i <= n; i++) printf("%d ", a[i].key);
    printf("\n");

    fprintf(out_fp, "%d\n", n);
    for (i = 1; i <= n; i++) fprintf(out_fp, "%d ", a[i].key);
    fprintf(out_fp, "\n");

    fclose(fp);
    fclose(out_fp);
    return 0;
}