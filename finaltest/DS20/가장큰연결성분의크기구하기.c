/*
 * [변형 문제 1] Largest Connected Component Size
 *
 * [문제 설명]
 * 무방향 그래프에서 가장 많은 정점을 포함하는 연결 성분의 크기(정점 개수)를 구하시오.
 *
 * [입력 예시]
 * 6 4
 * 1 2
 * 2 3
 * 4 5
 * 3 1
 *
 * [출력 예시]
 * Max Component Size: 3
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer graph[MAX_VERTICES];
int visited[MAX_VERTICES];
int n;
int currentSize = 0; // 현재 탐색 중인 컴포넌트 크기

void insert(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
}

void dfs(int v) {
    nodePointer w;
    visited[v] = 1;
    currentSize++; // 방문할 때마다 크기 증가
    for (w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex]) dfs(w->vertex);
    }
}

int main() {
    int m, u, v;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) graph[i] = NULL;
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        insert(u, v); insert(v, u);
    }

    int maxSize = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            currentSize = 0;
            dfs(i);
            if (currentSize > maxSize) maxSize = currentSize;
        }
    }

    printf("Max Component Size: %d\n", maxSize);
    return 0;
}