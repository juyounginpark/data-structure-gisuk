/*
 * [변형 문제 3] Recursive Merge Sort
 *
 * [문제 설명]
 * 재귀 호출을 이용한 합병 정렬(Merge Sort)을 구현하시오.
 *
 * [입력 예시]
 * 5
 * 5 2 4 1 3
 *
 * [출력 예시]
 * 1 2 3 4 5
 */

#include <stdio.h>
#define MAX_SIZE 100

int sorted[MAX_SIZE]; // 합병용 임시 배열

void merge(int list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (list[i] <= list[j]) sorted[k++] = list[i++];
        else sorted[k++] = list[j++];
    }
    while (i <= mid) sorted[k++] = list[i++];
    while (j <= right) sorted[k++] = list[j++];
    
    for (int l = left; l <= right; l++) list[l] = sorted[l];
}

void mergeSortRecursive(int list[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortRecursive(list, left, mid);
        mergeSortRecursive(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

int main() {
    int n, list[MAX_SIZE];
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", &list[i]); // 0-based indexing

    mergeSortRecursive(list, 0, n - 1);

    for(int i=0; i<n; i++) printf("%d ", list[i]);
    return 0;
}