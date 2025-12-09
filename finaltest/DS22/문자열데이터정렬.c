/*
 * [변형 문제 2] String Sort with Chain
 *
 * [문제 설명]
 * 문자열(이름)을 포함한 구조체를 사전 순(오름차순)으로 정렬하시오.
 *
 * [입력 예시]
 * 3
 * Apple
 * Banana
 * Cherry
 *
 * [출력 예시]
 * Apple Banana Cherry
 */
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct { char name[20]; } element;
element a[MAX_SIZE];
int link[MAX_SIZE];
int n;

int listMergeStr(element a[], int link[], int start1, int start2) {
    int last1 = start1, last2 = start2, lastResult = 0;
    while (last1 && last2) {
        // 문자열 비교 strcmp 사용
        if (strcmp(a[last1].name, a[last2].name) <= 0) {
            link[lastResult] = last1; lastResult = last1; last1 = link[last1];
        } else {
            link[lastResult] = last2; lastResult = last2; last2 = link[last2];
        }
    }
    link[lastResult] = (last1 == 0) ? last2 : last1;
    return link[0];
}

int rmergeSortStr(element a[], int link[], int left, int right) {
    if (left >= right) return left;
    int mid = (left + right) / 2;
    return listMergeStr(a, link, rmergeSortStr(a, link, left, mid), 
                                 rmergeSortStr(a, link, mid + 1, right));
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) { scanf("%s", a[i].name); link[i] = 0; }
    int head = rmergeSortStr(a, link, 1, n);
    while (head) { printf("%s ", a[head].name); head = link[head]; }
    return 0;
}