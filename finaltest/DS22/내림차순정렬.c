/*
 * [변형 문제 1] Descending Order Merge Sort
 *
 * [문제 설명]
 * link 배열을 이용한 합병 정렬을 수정하여 내림차순(큰 수 -> 작은 수)으로 정렬하시오.
 *
 * [입력 예시]
 * 5
 * 1 2 3 4 5
 *
 * [출력 예시]
 * 5 4 3 2 1
 */
#include <stdio.h>
#define MAX_SIZE 100

typedef struct { int key; } element;
element a[MAX_SIZE];
int link[MAX_SIZE];
int n;

int listMergeDesc(element a[], int link[], int start1, int start2) {
    int last1 = start1, last2 = start2, lastResult = 0;
    // 비교 연산자를 >= 로 변경하여 내림차순 구현
    for (; last1 && last2; ) {
        if (a[last1].key >= a[last2].key) { 
            link[lastResult] = last1; lastResult = last1; last1 = link[last1];
        } else {
            link[lastResult] = last2; lastResult = last2; last2 = link[last2];
        }
    }
    if (last1 == 0) link[lastResult] = last2;
    else link[lastResult] = last1;
    return link[0];
}

int rmergeSortDesc(element a[], int link[], int left, int right) {
    if (left >= right) return left;
    int mid = (left + right) / 2;
    int leftSorted = rmergeSortDesc(a, link, left, mid);
    int rightSorted = rmergeSortDesc(a, link, mid + 1, right);
    return listMergeDesc(a, link, leftSorted, rightSorted);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) { scanf("%d", &a[i].key); link[i] = 0; }
    int head = rmergeSortDesc(a, link, 1, n);
    while (head) { printf("%d ", a[head].key); head = link[head]; }
    return 0;
}