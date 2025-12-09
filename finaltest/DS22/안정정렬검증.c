/*
 * [변형 문제 3] Stable Sort Check
 *
 * [문제 설명]
 * (점수, 입력번호) 쌍을 점수 기준으로 오름차순 정렬하되, 
 * 점수가 같으면 입력번호가 빠른 순서가 유지되는지(Stable) 확인하시오.
 *
 * [입력 예시]
 * 3
 * 80 1
 * 80 2
 * 70 3
 *
 * [출력 예시]
 * (70, 3) (80, 1) (80, 2)
 */
#include <stdio.h>
#define MAX_SIZE 100

typedef struct { int score; int id; } element;
element a[MAX_SIZE];
int link[MAX_SIZE];
int n;

int listMergeStable(element a[], int link[], int start1, int start2) {
    int last1 = start1, last2 = start2, lastResult = 0;
    while (last1 && last2) {
        // <= 를 사용하면 앞쪽 리스트(먼저 입력된 것)가 먼저 선택되어 Stable 유지
        if (a[last1].score <= a[last2].score) {
            link[lastResult] = last1; lastResult = last1; last1 = link[last1];
        } else {
            link[lastResult] = last2; lastResult = last2; last2 = link[last2];
        }
    }
    link[lastResult] = (last1 == 0) ? last2 : last1;
    return link[0];
}

int rmergeSortStable(element a[], int link[], int left, int right) {
    if (left >= right) return left;
    int mid = (left + right) / 2;
    // LRV 방식 사용
    int l = rmergeSortStable(a, link, left, mid);
    int r = rmergeSortStable(a, link, mid + 1, right);
    return listMergeStable(a, link, l, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) { 
        scanf("%d %d", &a[i].score, &a[i].id); 
        link[i] = 0; 
    }
    int head = rmergeSortStable(a, link, 1, n);
    while (head) { 
        printf("(%d, %d) ", a[head].score, a[head].id); 
        head = link[head]; 
    }
    return 0;
}