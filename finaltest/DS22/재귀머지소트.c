/*
 * [문제] 자료구조응용 22: Recursive Merge Sort (Chain)
 *
 * [문제 설명]
 * 입력 파일(input.txt)로부터 데이터를 읽어 'link' 배열을 이용한 재귀적 합병 정렬을 수행하시오.
 * RLV(Right-Left-Visit) 방식과 LRV(Left-Right-Visit) 방식을 각각 구현하여
 * 정렬 과정에서 'listMerge'가 호출될 때마다 배열의 상태를 출력하시오.
 *
 * [입력 예시 (input.txt)]
 * 10
 * 26 5 77 1 61 11 59 15 48 19
 *
 * [출력 예시]
 * <<<<<<<<<< executing recursive merge sort (RLV) >>>>>>>>>>
 * listMerged(a, link, 9, 10)
 * ... (중간 과정 출력) ...
 * <<<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>>>>>
 * 1 5 11 15 19 26 48 59 61 77
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int key;
} element;

element a[MAX_SIZE];
int link[MAX_SIZE];
int n;

// 출력 헬퍼 함수
void printState(int start1, int start2) {
    printf("listMerged(a, link, %d, %d)\n", start1, start2);
    printf(" link: ");
    for (int i = 0; i <= n; i++) printf("%3d", link[i]);
    printf("\n    a: ");
    printf("   "); // 0번 인덱스 공백
    for (int i = 1; i <= n; i++) printf("%3d", a[i].key);
    printf("\n");
}

// Program 7.11: Merging sorted chains
int listMerge(element a[], int link[], int start1, int start2) {
    int last1, last2, lastResult;
    // link[0] is used as a temporary header
    for (last1 = start1, last2 = start2; last1 && last2; ) {
        if (a[last1].key <= a[last2].key) {
            link[lastResult] = last1;
            lastResult = last1;
            last1 = link[last1];
        }
        else {
            link[lastResult] = last2;
            lastResult = last2;
            last2 = link[last2];
        }
    }
    // attach remaining records
    if (last1 == 0) link[lastResult] = last2;
    else link[lastResult] = last1;

    // printState(start1, start2); // 디버깅/과제용 출력 위치
    return link[0];
}

// Program 7.10 (Modified): Recursive merge sort
// mode 0: RLV, mode 1: LRV
int rmergeSort(element a[], int link[], int left, int right, int mode) {
    if (left >= right) return left;
    
    int mid = (left + right) / 2;
    int leftSorted, rightSorted;

    if (mode == 0) { // RLV: Right -> Left -> Merge
        rightSorted = rmergeSort(a, link, mid + 1, right, mode);
        leftSorted = rmergeSort(a, link, left, mid, mode);
    }
    else { // LRV: Left -> Right -> Merge
        leftSorted = rmergeSort(a, link, left, mid, mode);
        rightSorted = rmergeSort(a, link, mid + 1, right, mode);
    }
    
    int mergedHead = listMerge(a, link, leftSorted, rightSorted);
    printState(leftSorted, rightSorted); // 병합 직후 상태 출력
    return mergedHead;
}

void runSort(int mode) {
    // 초기화: 각 노드는 독립적인 체인 (link[i] = 0)
    for (int i = 1; i <= n; i++) link[i] = 0;
    link[0] = 0;

    printf("\n<<<<<<<< executing recursive merge sort (%s) >>>>>>>>\n", mode == 0 ? "RLV" : "LRV");
    int head = rmergeSort(a, link, 1, n, mode);

    printf("<<<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>>>>>\n");
    int curr = head;
    while (curr != 0) {
        printf("%d ", a[curr].key);
        curr = link[curr];
    }
    printf("\n");
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (!fp) {
        // 파일 없으면 예제 데이터 사용
        n = 10;
        int data[] = { 0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19 };
        for (int i = 1; i <= n; i++) a[i].key = data[i];
    } else {
        fscanf(fp, "%d", &n);
        for (int i = 1; i <= n; i++) fscanf(fp, "%d", &a[i].key);
        fclose(fp);
    }

    // RLV 실행
    runSort(0);

    // LRV 실행 (데이터 재로드 필요 없으므로 링크만 초기화하면 됨)
    runSort(1);

    return 0;
}