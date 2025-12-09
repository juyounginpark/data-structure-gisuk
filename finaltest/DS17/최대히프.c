/*
 * [문제 1] 최대 히프(Max Heap) 구현
 *
 * [문제 설명]
 * 입력 파일(input.txt)로부터 데이터를 읽어 최대 히프를 구성하고,
 * 구성된 히프에서 최대값을 하나씩 삭제하며 매 단계마다 배열의 상태를 출력한다.
 *
 * [입력]
 * 파일: input.txt (내용: 10 40 30 5 12 6 15 9 60)
 *
 * [출력]
 * - 삽입(Insertion) 과정: 매 데이터 입력 시마다 히프 배열 상태 출력
 * - 삭제(Deletion) 과정: 최대값 삭제 시마다 히프 배열 상태 출력
 *
 * [참고]
 * Program 5.13 (Insertion), Program 5.14 (Deletion) 알고리즘 적용 [cite: 181, 212]
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    int key;
} element;

element heap[MAX_ELEMENTS];
int n = 0;

// 히프 상태 출력 함수
void printHeap(int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i].key);
    }
    printf("\n");
}

// 최대 히프 삽입 (Program 5.13) [cite: 169-181]
void push(element item, int* n) {
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    i = ++(*n);
    // 부모 노드(i/2)보다 키값이 크면 부모를 끌어내림
    while ((i != 1) && (item.key > heap[i / 2].key)) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = item;
}

// 최대 히프 삭제 (Program 5.14) [cite: 183-211]
element pop(int* n) {
    int parent, child;
    element item, temp;

    if (HEAP_EMPTY(*n)) {
        fprintf(stderr, "The heap is empty\n");
        exit(EXIT_FAILURE);
    }

    item = heap[1];      // 삭제할 최대값(루트)
    temp = heap[(*n)--]; // 힙의 마지막 노드
    parent = 1;
    child = 2;

    while (child <= *n) {
        // 현재 노드의 자식 중 더 큰 자식을 찾음
        if ((child < *n) && (heap[child].key < heap[child + 1].key))
            child++;
        
        // 마지막 노드가 더 큰 자식보다 크면 위치 확정 (반복 종료)
        if (temp.key >= heap[child].key) break;

        // 자식이 더 크면 자식을 부모 자리로 올림
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다. (input.txt 확인 필요)\n");
        // 파일이 없을 경우 PDF 예시 데이터를 하드코딩으로 처리 (테스트용)
        printf("파일이 없어 기본 예시 데이터로 진행합니다.\n");
        int defaultData[] = { 10, 40, 30, 5, 12, 6, 15, 9, 60 };
        
        printf("***** insertion into a max heap *****\n");
        for (int i = 0; i < 9; i++) {
            element item;
            item.key = defaultData[i];
            push(item, &n);
            printHeap(n);
        }
    }
    else {
        element item;
        printf("***** insertion into a max heap *****\n");
        while (fscanf(fp, "%d", &item.key) != EOF) {
            push(item, &n);
            printHeap(n);
        }
        fclose(fp);
    }

    printf("***** deletion from a max heap *****\n");
    // 힙이 빌 때까지 반복 삭제
    int currentSize = n;
    for (int i = 0; i < currentSize; i++) {
        pop(&n);
        printHeap(n);
    }

    return 0;
}