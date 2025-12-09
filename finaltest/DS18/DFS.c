/*
 * [변형 문제 2] 깊이 우선 탐색 (DFS)
 *
 * [문제 설명]
 * 정점 0부터 시작하여 그래프를 깊이 우선 탐색(DFS)한 순서를 출력하시오.
 * (방문 배열 visited 사용)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define FALSE 0
#define TRUE 1

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer adjLists[MAX_VERTICES];
int visited[MAX_VERTICES];

void insertFront(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = adjLists[u];
    adjLists[u] = newNode;
}

// DFS 재귀 함수
void dfs(int v) {
    nodePointer w;
    visited[v] = TRUE;
    printf("%d ", v); // 방문 정점 출력
    
    for (w = adjLists[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex);
        }
    }
}

int main() {
    // 테스트 데이터 (G3 예시: 0->1, 1->2, 1->0)
    int n = 3;
    insertFront(0, 1); 
    insertFront(1, 2); 
    insertFront(1, 0); // 방향 그래프 가정 시 입력 주의, 여기선 단순 연결 테스트
    
    // 초기화
    for(int i=0; i<n; i++) visited[i] = FALSE;
    
    printf("=== DFS Traversal ===\n");
    dfs(0);
    printf("\n");
    
    return 0;
}