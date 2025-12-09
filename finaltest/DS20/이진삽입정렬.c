/*
 * [변형 문제 5] Binary Insertion Sort
 *
 * [문제 설명]
 * 삽입 정렬의 위치 탐색 과정을 이진 탐색으로 최적화하여 정렬하시오.
 *
 * [입력 예시]
 * 5
 * 5 2 4 1 3
 *
 * [출력 예시]
 * 1 2 3 4 5
 */

#include <stdio.h>

// 이진 탐색으로 삽입 위치 찾기
int binarySearch(int a[], int item, int low, int high) {
    if (high <= low)
        return (item > a[low]) ? (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == a[mid])
        return mid + 1;

    if (item > a[mid])
        return binarySearch(a, item, mid + 1, high);
    return binarySearch(a, item, low, mid - 1);
}

void binaryInsertionSort(int a[], int n) {
    int i, loc, j, selected;

    for (i = 1; i < n; i++) {
        j = i - 1;
        selected = a[i];

        // 0 ~ i-1 범위에서 들어갈 위치 찾기
        loc = binarySearch(a, selected, 0, j);

        // 데이터 밀어내기
        while (j >= loc) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int a[100]; // 0-based indexing for this logic
    for(int i=0; i<n; i++) scanf("%d", &a[i]);

    binaryInsertionSort(a, n);

    for(int i=0; i<n; i++) printf("%d ", a[i]);
    return 0;
}