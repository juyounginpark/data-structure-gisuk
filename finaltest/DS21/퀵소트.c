/*
 * [문제 1] Quick Sort
 *
 * [문제 설명]
 * 입력 파일(input.txt)로부터 데이터를 읽어 퀵 정렬(Quick Sort)을 수행하시오.
 * 각 재귀 호출마다 배열의 상태를 출력하고, 총 호출 횟수를 계산하여 출력하시오.
 *
 * [입력 예시 (input.txt)]
 * 11
 * 12 2 16 30 8 28 4 10 20 6 18
 *
 * [출력 예시]
 * execution of quick sort
 * [1] [2] ... [11]
 * [left 1, right 11]
 * 12  2  16 ... 18
 * ... (각 단계별 출력) ...
 * calls of quick sort: 15 calls
 * >>> Sorted List <<<
 * 2 4 6 8 10 12 16 18 20 28 30
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
int calls = 0; // 호출 횟수 카운트

void printList(element a[], int size) {
    for (int i = 1; i <= size; i++) {
        printf("%4d", a[i].key);
    }
    printf("\n");
}

// Program 7.6: Quick sort
void quickSort(element a[], int left, int right) {
    calls++; // 함수 호출 시 카운트 증가
    int pivot, i, j;
    element temp;

    if (left < right) {
        i = left;
        j = right + 1;
        pivot = a[left].key;

        // 현재 호출 상태 출력 (문제 요구사항: left, right 범위 및 배열 상태)
        printf("[left %2d, right %2d]\n", left, right);
        printList(a, n);

        do {
            do { i++; } while (i <= right && a[i].key < pivot);
            do { j--; } while (j > left && a[j].key > pivot);
            if (i < j) SWAP(a[i], a[j], temp);
        } while (i < j);

        SWAP(a[left], a[j], temp);

        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

int main() {
    FILE* fp_in = fopen("input.txt", "r");
    FILE* fp_out = fopen("output.txt", "w");
    
    if (!fp_in) {
        printf("input.txt 파일을 찾을 수 없습니다.\n");
        return 1;
    }

    // 1. 입력 파일로부터 데이터 읽기
    fscanf(fp_in, "%d", &n);
    for (int i = 1; i <= n; i++) {
        fscanf(fp_in, "%d", &list[i].key);
    }

    printf("<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    printList(list, n);
    printf("\nexecution of quick sort\n");
    
    // 헤더 출력 (인덱스)
    for(int i=1; i<=n; i++) printf("[%2d]", i);
    printf("\n");

    // 2. 퀵 정렬 수행
    quickSort(list, 1, n);

    printf("\ncalls of quick sort: %d calls\n", calls);

    // 3. 정렬 결과 출력 및 파일 저장
    printf("\n>>>>>>>>>>>>>>>>>>>> Sorted List\n");
    printList(list, n);

    fprintf(fp_out, "%d\n", n);
    for (int i = 1; i <= n; i++) {
        fprintf(fp_out, "%d ", list[i].key);
    }

    fclose(fp_in);
    fclose(fp_out);

    return 0;
}