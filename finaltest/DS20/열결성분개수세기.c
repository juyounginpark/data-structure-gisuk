/*
 * [변형 문제 2] Count Connected Components
 *
 * [문제 설명]
 * 그래프가 몇 개의 독립된 연결 성분으로 이루어져 있는지 개수를 세어 출력하시오.
 *
 * [입력 예시]
 * 5 2
 * 1 2
 * 4 5
 *
 * [출력 예시]
 * Number of Components: 3 ( {1,2}, {3}, {4,5} )
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
typedef struct node* nodePointer;
typedef struct node { int vertex; nodePointer link; } Node;
nodePointer graph[MAX_VERTICES];
int visited[MAX_VERTICES];

void insert(int u, int v) {
    nodePointer temp = (nodePointer)malloc(sizeof(Node));
    temp->vertex = v; temp->link = graph[u]; graph[u] = temp;
}

void dfs(int v) {
    visited[v] = 1;
    for (nodePointer w = graph[v]; w; w = w->link)
        if (!visited[w->vertex]) dfs(w->vertex);
}

int main() {
    int n, m, u, v;
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; i++) {
        scanf("%d %d", &u, &v);
        insert(u, v); insert(v, u);
    }

    int count = 0;
    for (int i = 1; i <= n; i++) { // 1번 정점부터 시작 가정
        if (!visited[i]) {
            count++;
            dfs(i);
        }
    }
    printf("Number of Components: %d\n", count);
    return 0;
}