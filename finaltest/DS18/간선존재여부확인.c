/*
 * [변형 문제 5] 간선 존재 여부 확인 (Exist Edge)
 *
 * [문제 설명]
 * 두 정점 u, v를 입력받아 간선이 존재하면 "Exist", 없으면 "Not Exist"를 출력하시오.
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

int hasEdge(int u, int v) {
    nodePointer curr = adjLists[u];
    while (curr) {
        if (curr->vertex == v) return 1; // 찾음
        curr = curr->link;
    }
    return 0; // 못 찾음
}

int main() {
    // 테스트 데이터: 0->1 연결
    insertFront(0, 1);
    
    int u = 0, v = 1;
    if (hasEdge(u, v)) printf("Edge (%d, %d): Exist\n", u, v);
    else printf("Edge (%d, %d): Not Exist\n", u, v);
    
    u = 0, v = 2;
    if (hasEdge(u, v)) printf("Edge (%d, %d): Exist\n", u, v);
    else printf("Edge (%d, %d): Not Exist\n", u, v);
    
    return 0;
}