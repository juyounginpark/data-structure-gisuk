/*
 * [변형 문제 4] 연결 성분 개수 (Connected Components)
 *
 * [문제 설명]
 * 그래프 내에 서로 연결되지 않은 부분 그래프가 몇 개인지 세어 출력하시오.
 * (모든 정점을 순회하며 DFS/BFS 호출 횟수 카운트)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

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

void dfs(int v) {
    nodePointer w;
    visited[v] = TRUE;
    for (w = adjLists[v]; w; w = w->link) {
        if (!visited[w->vertex]) dfs(w->vertex);
    }
}

int main() {
    // 테스트 데이터: (0-1), (2-3) -> 두 개의 덩어리
    int n = 4;
    insertFront(0, 1); insertFront(1, 0);
    insertFront(2, 3); insertFront(3, 2);
    
    for(int i=0; i<n; i++) visited[i] = FALSE;
    
    int count = 0;
    for(int i=0; i<n; i++) {
        if(!visited[i]) { // 방문하지 않은 정점이 있다면 새로운 컴포넌트 시작
            count++;
            dfs(i);
        }
    }
    
    printf("Number of Connected Components: %d\n", count);
    return 0;
}