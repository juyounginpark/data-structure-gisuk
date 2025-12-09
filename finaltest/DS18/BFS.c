/*
 * [변형 문제 3] 너비 우선 탐색 (BFS)
 *
 * [문제 설명]
 * 정점 0부터 시작하여 그래프를 너비 우선 탐색(BFS)한 순서를 출력하시오.
 * (원형 큐 활용)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define MAX_QUEUE 100
#define TRUE 1
#define FALSE 0

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer adjLists[MAX_VERTICES];
int visited[MAX_VERTICES];
int queue[MAX_QUEUE];
int front = 0, rear = 0;

void addq(int v) { queue[++rear] = v; }
int deleteq() { return queue[++front]; }
int isQueueEmpty() { return front == rear; }

void insertFront(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = adjLists[u];
    adjLists[u] = newNode;
}

void bfs(int v) {
    nodePointer w;
    printf("%d ", v);
    visited[v] = TRUE;
    addq(v);
    
    while(!isQueueEmpty()) {
        v = deleteq();
        for(w = adjLists[v]; w; w = w->link) {
            if(!visited[w->vertex]) {
                printf("%d ", w->vertex);
                addq(w->vertex);
                visited[w->vertex] = TRUE;
            }
        }
    }
}

int main() {
    // 테스트 데이터
    int n = 4; 
    // 0-1, 0-2, 1-2, 2-0, 2-3 연결 가정
    insertFront(0, 1); insertFront(0, 2);
    insertFront(1, 2); 
    insertFront(2, 0); insertFront(2, 3);
    
    for(int i=0; i<n; i++) visited[i] = FALSE;
    
    printf("=== BFS Traversal ===\n");
    bfs(0);
    printf("\n");
    return 0;
}