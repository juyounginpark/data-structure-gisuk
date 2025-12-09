/*
 * [변형 문제 4] Count Comparisons
 *
 * [문제 설명]
 * 재귀적 합병 정렬을 수행하면서 요소 간의 비교 연산(<=)이 총 몇 번 수행되는지 출력하시오.
 *
 * [입력 예시]
 * 5
 * 5 4 3 2 1
 *
 * [출력 예시]
 * Comparisons: 8 (예시 값, 실제 구현에 따라 다름)
 */
#include <stdio.h>
#define MAX_SIZE 100

typedef struct { int key; } element;
element a[MAX_SIZE];
int link[MAX_SIZE];
int n;
int comparisons = 0;

int listMergeCount(element a[], int link[], int start1, int start2) {
    int last1 = start1, last2 = start2, lastResult = 0;
    while (last1 && last2) {
        comparisons++; // 비교 카운트 증가
        if (a[last1].key <= a[last2].key) {
            link[lastResult] = last1; lastResult = last1; last1 = link[last1];
        } else {
            link[lastResult] = last2; lastResult = last2; last2 = link[last2];
        }
    }
    link[lastResult] = (last1 == 0) ? last2 : last1;
    return link[0];
}

int rmergeSortCount(element a[], int link[], int left, int right) {
    if (left >= right) return left;
    int mid = (left + right) / 2;
    int l = rmergeSortCount(a, link, left, mid);
    int r = rmergeSortCount(a, link, mid + 1, right);
    return listMergeCount(a, link, l, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) { scanf("%d", &a[i].key); link[i] = 0; }
    rmergeSortCount(a, link, 1, n);
    printf("Comparisons: %d\n", comparisons);
    return 0;
}