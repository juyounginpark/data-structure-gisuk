/*
 * [문제] 연결 요소의 개수 구하기
 *
 * [문제 설명]
 * 방향 없는 그래프가 주어졌을 때, 연결 요소(Connected Component)의 개수를 구하시오.
 *
 * [입력 예시]
 * 6 5      (정점 N=6, 간선 M=5)
 * 1 2
 * 2 5
 * 5 1
 * 3 4
 * 4 6
 *
 * [출력 예시]
 * 2        ( {1,2,5}, {3,4,6} 두 덩어리이므로 )
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

void insert(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
}

void dfs(int v) {
    visited[v] = TRUE;
    for (nodePointer w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex);
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) graph[i] = NULL; // 1번부터 시작한다고 가정
    for (int i = 1; i <= N; i++) visited[i] = FALSE;

    int u, v;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &u, &v);
        insert(u, v);
        insert(v, u);
    }

    int components = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i);
            components++;
        }
    }

    printf("%d\n", components);
    return 0;
}