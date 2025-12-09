/*
 * [문제 2] Radix Sort
 *
 * [문제 설명]
 * 입력 파일로부터 데이터를 읽어 기수 정렬(Radix Sort, LSD)을 수행하시오.
 * 각 패스(Pass)마다 link 배열과 result(체인 순서대로 나열된 값)를 출력하시오.
 *
 * [입력 예시 (input.txt)]
 * 11
 * 12 2 16 30 8 28 4 10 20 6 18
 *
 * [출력 예시]
 * ****** initial chain ******
 * link: 2 3 4 ...
 * a: 12 2 16 ...
 * result: 12 2 16 ...
 * **** pass 1 ****
 * link: 2 7 10 ...
 * result: 30 10 20 ...
 * ...
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int key;
} element;

element list[MAX_SIZE];
int link[MAX_SIZE];
int n;

// 특정 자릿수 반환 함수 (r=10 고정)
int digit(int key, int i, int r) {
    int d, val = key;
    for (d = 0; d < i; d++) {
        val /= r;
    }
    return val % r;
}

// 체인 순서대로 출력하는 함수
void printList(int first) {
    printf("result: ");
    int curr = first;
    while (curr) {
        printf("%d ", list[curr].key);
        curr = link[curr];
    }
    printf("\n");
}

// 큐 상태 출력 함수
void printQueues(int front[], int rear[], int r) {
    printf("[idx] ");
    for(int i=0; i<r; i++) printf("[%d] ", i);
    printf("\nrear: ");
    for(int i=0; i<r; i++) printf("%2d  ", rear[i]);
    printf("\nfront:");
    for(int i=0; i<r; i++) printf("%2d  ", front[i]);
    printf("\n");
}

// Program 7.14: LSD radix sort
int radixSort(element a[], int link[], int d, int r, int n) {
    int* front = (int*)malloc(sizeof(int) * r);
    int* rear = (int*)malloc(sizeof(int) * r);
    int i, bin, current, first, last;

    // create initial chain
    first = 1;
    for (i = 1; i < n; i++) link[i] = i + 1;
    link[n] = 0;

    printf("****** initial chain ******\n");
    printf("link: "); for(int k=1; k<=n; k++) printf("%d ", link[k]); printf("\n");
    printf("first: %d\n", first);
    printList(first);

    for (i = 0; i < d; i++) {
        // initialize bins
        for (bin = 0; bin < r; bin++) front[bin] = rear[bin] = 0; // rear도 0 초기화

        // distribute
        for (current = first; current; current = link[current]) {
            bin = digit(a[current].key, i, r);
            if (front[bin] == 0) front[bin] = current;
            else link[rear[bin]] = current;
            rear[bin] = current;
        }

        // collect
        for (bin = 0; !front[bin]; bin++); // find first nonempty
        first = front[bin];
        last = rear[bin];

        for (bin++; bin < r; bin++) {
            if (front[bin]) {
                link[last] = front[bin];
                last = rear[bin];
            }
        }
        link[last] = 0;

        // Pass 결과 출력
        printf("\n**** pass %d ****\n", i + 1);
        printf("link: "); for(int k=1; k<=n; k++) printf("%d ", link[k]); printf("\n");
        printf("first: %d\n", first);
        printList(first);
        printQueues(front, rear, r);
    }

    free(front);
    free(rear);
    return first;
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (!fp) return 1;

    // 문제 2에서 d는 자릿수(예: 2자리 수면 2, 3자리 수면 3)
    // 여기선 PDF 예시 데이터(최대 30 -> 2자리)에 맞춰 d=2로 설정하거나
    // 데이터의 최댓값을 보고 d를 결정해야 함.
    // Case 1 데이터(최대 30) -> d=2
    // Case 2 데이터(최대 984) -> d=3
    int d = 2; // 기본값
    
    fscanf(fp, "%d", &n);
    int maxKey = 0;
    for (int i = 1; i <= n; i++) {
        fscanf(fp, "%d", &list[i].key);
        if (list[i].key > maxKey) maxKey = list[i].key;
    }
    
    // 자릿수 d 자동 계산
    d = 0;
    while(maxKey > 0) { maxKey /= 10; d++; }
    if(d == 0) d = 1;

    int r = 10;
    int first = radixSort(list, link, d, r, n);

    return 0;
}