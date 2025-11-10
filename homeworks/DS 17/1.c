/*
2025002720
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int heap[MAX_SIZE];
int n = 0;

void printHeap() {
    for (int i = 1; i <= n; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

void insertHeap(int item) {
    int i = ++n;
    while (i != 1 && item > heap[i / 2]) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = item;
}

int deleteHeap() {
    int parent, child;
    int item, temp;
    item = heap[1];
    temp = heap[n--];
    parent = 1;
    child = 2;
    while (child <= n) {
        if (child < n && heap[child] < heap[child + 1])
            child++;
        if (temp >= heap[child]) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("input.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    int num;
    printf("***** insertion into a max heap *****\n");
    while (fscanf(fp, "%d", &num) != EOF) {
        insertHeap(num);
        printHeap();
    }
    fclose(fp);

    printf("\n***** deletion from a max heap *****\n");
    for (int i = n; i > 0; i--) {
        deleteHeap();
        printHeap();
    }

    return 0;
}
