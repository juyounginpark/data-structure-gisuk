/*
 * [변형 문제 4] Find K-th Smallest Element
 *
 * [문제 설명]
 * N개의 수가 주어졌을 때, K번째로 작은 수를 구하시오. (Quick Select 알고리즘 활용)
 *
 * [입력 예시]
 * 5 2      (N=5, K=2)
 * 5 1 4 3 2
 *
 * [출력 예시]
 * 2        (정렬 시 1, 2, 3, 4, 5 이므로 2번째는 2)
 */

#include <stdio.h>
#define SWAP(x, y, t) { t = x; x = y; y = t; }

int partition(int a[], int left, int right) {
    int pivot = a[left];
    int i = left, j = right + 1;
    int temp;
    do {
        do { i++; } while (i <= right && a[i] < pivot);
        do { j--; } while (j > left && a[j] > pivot);
        if (i < j) SWAP(a[i], a[j], temp);
    } while (i < j);
    SWAP(a[left], a[j], temp);
    return j;
}

int quickSelect(int a[], int left, int right, int k) {
    if (left <= right) {
        int p = partition(a, left, right);
        if (p == k) return a[p]; // K번째 위치 찾음
        else if (p > k) return quickSelect(a, left, p - 1, k); // 왼쪽 탐색
        else return quickSelect(a, p + 1, right, k); // 오른쪽 탐색
    }
    return -1;
}

int main() {
    int n, k, a[100];
    scanf("%d %d", &n, &k);
    for(int i=1; i<=n; i++) scanf("%d", &a[i]);

    printf("%d\n", quickSelect(a, 1, n, k));
    return 0;
}