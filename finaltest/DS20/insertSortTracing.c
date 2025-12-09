/*
 * [문제 2] Insertion Sort Tracing
 *
 * [문제 설명]
 * 입력 리스트 {12, 2, 16, 30, 8, 28, 4, 10, 20, 6, 18} 에 대해
 * Insertion Sort의 각 단계별 배열 상태를 출력하시오.
 *
 * [입력]
 * (코드 내 배열 초기화)
 *
 * [출력]
 * Pass 1: ...
 * Pass 2: ...
 */

#include <stdio.h>

typedef struct {
    int key;
} element;

// Program 7.4: Insertion into a sorted list [cite: 131-137]
// 1-based indexing을 사용하므로 a[0]는 sentinel로 사용
void insert(element e, element a[], int i) {
    a[0] = e; // sentinel
    while (e.key < a[i].key) {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}

// Program 7.5: Insertion sort [cite: 139-146]
void insertionSort(element a[], int n) {
    int j;
    for (j = 2; j <= n; j++) {
        element temp = a[j];
        insert(temp, a, j - 1);

        // 출력용 코드 (문제 요구사항인 배열 상태 확인)
        printf("Pass %2d: ", j - 1);
        for (int k = 1; k <= n; k++) {
            printf("%d ", a[k].key);
        }
        printf("\n");
    }
}

int main() {
    // 1-based indexing을 위해 0번 인덱스는 비워둠
    element list[] = { {0}, {12}, {2}, {16}, {30}, {8}, {28}, {4}, {10}, {20}, {6}, {18} };
    int n = 11;

    printf("Initial: ");
    for (int k = 1; k <= n; k++) printf("%d ", list[k].key);
    printf("\n\n");

    insertionSort(list, n);

    return 0;
}