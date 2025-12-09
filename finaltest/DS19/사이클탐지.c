/*
 * [문제] 그래프 사이클 판별
 *
 * [문제 설명]
 * 무방향 그래프에서 사이클(Cycle)이 존재하는지 판별하시오.
 *
 * [입력 예시]
 * 3 3
 * 0 1
 * 1 2
 * 2 0
 *
 * [출력 예시]
 * Cycle Found
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 55
#define TRUE 1
#define FALSE 0

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer graph[MAX_VERTICES];
int visited[MAX_VERTICES];
int hasCycle = FALSE;

void insert(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
}

void dfs(int v, int parent) {
    if (hasCycle) return;
    visited[v] = TRUE;

    for (nodePointer w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex, v);
        }
        else if (w->vertex != parent) { // 방문했었는데 부모가 아니면 사이클
            hasCycle = TRUE;
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) graph[i] = NULL;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        insert(u, v);
        insert(v, u);
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) dfs(i, -1);
    }

    if (hasCycle) printf("Cycle Found\n");
    else printf("No Cycle\n");

    return 0;
}