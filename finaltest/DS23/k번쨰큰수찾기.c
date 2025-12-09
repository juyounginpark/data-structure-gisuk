/*
 * [변형 문제 2] Find K-th Largest Element using Heap
 *
 * [문제 설명]
 * N개의 수 중 K번째로 큰 수를 히프 자료구조를 이용하여 찾으시오.
 *
 * [입력 예시]
 * 5 2
 * 1 5 2 4 3
 *
 * [출력 예시]
 * 4
 */
#include <stdio.h>
#define SWAP(x, y, t) { t = x; x = y; y = t; }

// adjust 함수 (Max Heap) 재사용
void adjust(int a[], int root, int n) {
    int child, temp = a[root], rootkey = a[root];
    child = 2 * root;
    while (child <= n) {
        if ((child < n) && (a[child] < a[child + 1])) child++;
        if (rootkey > a[child]) break;
        a[child / 2] = a[child]; child *= 2;
    }
    a[child / 2] = temp;
}

int main() {
    int n, k, a[100], temp;
    scanf("%d %d", &n, &k);
    for(int i=1; i<=n; i++) scanf("%d", &a[i]);

    // Build Max Heap
    for(int i=n/2; i>0; i--) adjust(a, i, n);

    // K-1번 pop
    for(int i=0; i<k-1; i++) {
        SWAP(a[1], a[n-i], temp);
        adjust(a, 1, n-i-1);
    }
    printf("%d\n", a[1]); // K번째 큰 수 (현재 루트)
    return 0;
}