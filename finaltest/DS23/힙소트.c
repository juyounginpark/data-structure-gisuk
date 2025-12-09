/*
 * [문제 1] Heap Sort
 *
 * [문제 설명]
 * 입력 파일(input.txt)로부터 데이터를 읽어 Max Heap을 구성한 후,
 * 힙 정렬을 수행하시오. 각 단계별로 배열의 상태를 출력하시오.
 *
 * [입력 예시 (input.txt)]
 * 11
 * 12 2 16 30 8 28 4 10 20 6 18
 *
 * [출력 예시]
 * <<<<<<<<<<<<<< Input List >>>>>>>>>>>>>
 * 12 2 16 ...
 * <<<<<<<< executing heap sort >>>>>>>>>>
 * after initialization of max heap...
 * 30 20 28 ...
 * step 1: ...
 * ...
 * <<<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>
 * 2 4 6 ...
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define SWAP(x, y, t) { t = x; x = y; y = t; }

typedef struct {
    int key;
} element;

element list[MAX_SIZE];
int n;

void printArray(element a[], int size) {
    for (int i = 1; i <= size; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");
}

// Program 7.12: Adjusting a max heap
void adjust(element a[], int root, int n) {
    int child, rootkey;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root;
    while (child <= n) {
        if ((child < n) && (a[child].key < a[child + 1].key))
            child++;
        if (rootkey > a[child].key)
            break;
        else {
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

// Program 7.13: Heap sort
void heapSort(element a[], int n) {
    int i;
    element temp;

    // 1. 초기 Max Heap 구성
    for (i = n / 2; i > 0; i--)
        adjust(a, i, n);

    printf("after initialization of max heap...\n");
    printArray(a, n);
    printf("\n");

    // 2. 힙 정렬 수행 (Max 삭제 -> 배열 뒤로 이동)
    for (i = n - 1; i > 0; i--) {
        SWAP(a[1], a[i + 1], temp);
        adjust(a, 1, i);
        printf("step %2d: ", n - i);
        printArray(a, n);
    }
}

int main() {
    FILE* fp_in = fopen("input.txt", "r");
    FILE* fp_out = fopen("output.txt", "w");
    
    if (!fp_in) {
        printf("input.txt 파일을 찾을 수 없습니다.\n");
        return 1;
    }

    fscanf(fp_in, "%d", &n);
    for (int i = 1; i <= n; i++) {
        fscanf(fp_in, "%d", &list[i].key);
    }

    printf("<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    printArray(list, n);
    printf("\n<<<<<<<< executing heap sort >>>>>>>>>>\n");
    
    heapSort(list, n);

    printf("\n<<<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>\n");
    printArray(list, n);

    // 파일 저장
    fprintf(fp_out, "%d\n", n);
    for (int i = 1; i <= n; i++) {
        fprintf(fp_out, "%d ", list[i].key);
    }

    fclose(fp_in);
    fclose(fp_out);

    return 0;
}