/*
 * [문제] 두 정점 사이의 경로 출력
 *
 * [문제 설명]
 * 시작 정점 S에서 도착 정점 E로 가는 단순 경로를 찾아 순서대로 출력하시오.
 * (DFS 방문 순서를 기준으로 함)
 *
 * [입력 예시]
 * 4 4
 * 0 1
 * 1 2
 * 2 3
 * 0 2
 * 0 3      (Start=0, End=3)
 *
 * [출력 예시]
 * 0 2 3    (0에서 2를 거쳐 3으로 가는 경로)
 * ※ 인접 리스트 구성 순서에 따라 0 1 2 3이 나올 수도 있음
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
int path[MAX_VERTICES];
int pathIdx = 0;
int found = FALSE;

void insert(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
}

void dfs(int v, int target) {
    visited[v] = TRUE;
    path[pathIdx++] = v;

    if (v == target) {
        found = TRUE;
        return;
    }

    for (nodePointer w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex] && !found) {
            dfs(w->vertex, target);
        }
    }

    if (!found) pathIdx--; // Backtracking
}

int main() {
    int N, M, S, E;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) graph[i] = NULL;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        insert(u, v);
        insert(v, u);
    }

    scanf("%d %d", &S, &E);

    dfs(S, E);

    if (found) {
        for (int i = 0; i < pathIdx; i++) printf("%d ", path[i]);
        printf("\n");
    } else {
        printf("No Path\n");
    }

    return 0;
}