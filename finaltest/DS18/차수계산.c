/*
 * [변형 문제 1] 차수(Degree) 계산
 *
 * [문제 설명]
 * 구성된 무방향 그래프의 인접 리스트를 순회하여, 각 정점의 차수(Degree)를 출력하시오.
 *
 * [입력]
 * (input.txt) - 무방향 그래프 예시 사용
 *
 * [출력]
 * Vertex 0 degree: 3
 * Vertex 1 degree: 3
 * ...
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer adjLists[MAX_VERTICES];

void insertFront(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = adjLists[u];
    adjLists[u] = newNode;
}

// 차수 계산 함수
int getDegree(int u) {
    int count = 0;
    nodePointer curr = adjLists[u];
    while (curr) {
        count++;
        curr = curr->link;
    }
    return count;
}

int main() {
    // 테스트 데이터 (직접 입력 또는 파일 입력 대체)
    // 예: u 4 6 과 동일한 구조 생성
    int n = 4;
    insertFront(0, 1); insertFront(1, 0);
    insertFront(0, 2); insertFront(2, 0);
    insertFront(0, 3); insertFront(3, 0);
    insertFront(1, 2); insertFront(2, 1);
    insertFront(1, 3); insertFront(3, 1);
    insertFront(2, 3); insertFront(3, 2);

    printf("=== Vertex Degrees ===\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d degree: %d\n", i, getDegree(i));
    }
    return 0;
}