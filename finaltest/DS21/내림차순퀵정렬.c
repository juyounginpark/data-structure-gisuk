/*
 * [변형 문제 1] Quick Sort Descending
 *
 * [문제 설명]
 * 퀵 정렬을 이용하여 데이터를 내림차순(큰 수 -> 작은 수)으로 정렬하시오.
 *
 * [입력 예시]
 * 5
 * 5 2 4 1 3
 *
 * [출력 예시]
 * 5 4 3 2 1
 */

#include <stdio.h>
#define SWAP(x, y, t) { t = x; x = y; y = t; }

void quickSortDesc(int a[], int left, int right) {
    int pivot, i, j;
    int temp;

    if (left < right) {
        i = left;
        j = right + 1;
        pivot = a[left];

        do {
            // 오름차순과 반대로, pivot보다 큰 값을 찾을 때까지 i 증가
            do { i++; } while (i <= right && a[i] > pivot);
            // pivot보다 작은 값을 찾을 때까지 j 감소
            do { j--; } while (j > left && a[j] < pivot);
            if (i < j) SWAP(a[i], a[j], temp);
        } while (i < j);

        SWAP(a[left], a[j], temp);
        quickSortDesc(a, left, j - 1);
        quickSortDesc(a, j + 1, right);
    }
}

int main() {
    int n, a[100];
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%d", &a[i]);

    quickSortDesc(a, 1, n);

    for(int i=1; i<=n; i++) printf("%d ", a[i]);
    return 0;
}