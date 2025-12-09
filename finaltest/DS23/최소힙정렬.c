/*
 * [변형 문제 1] Min Heap Sort (Descending Order)
 *
 * [문제 설명]
 * 최소 히프(Min Heap)를 이용하여 데이터를 내림차순(큰 수 -> 작은 수)으로 정렬하시오.
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

void adjustMin(int a[], int root, int n) {
    int child, rootkey, temp;
    temp = a[root];
    rootkey = a[root];
    child = 2 * root;
    while (child <= n) {
        // 더 작은 자식을 선택 (Min Heap 조건)
        if ((child < n) && (a[child] > a[child + 1])) child++;
        if (rootkey <= a[child]) break;
        else {
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

void minHeapSort(int a[], int n) {
    int i, temp;
    for (i = n / 2; i > 0; i--) adjustMin(a, i, n);
    for (i = n - 1; i > 0; i--) {
        SWAP(a[1], a[i + 1], temp);
        adjustMin(a, 1, i);
    }
}

int main() {
    int n, a[100];
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%d", &a[i]);
    minHeapSort(a, n);
    for(int i=1; i<=n; i++) printf("%d ", a[i]);
    return 0;
}