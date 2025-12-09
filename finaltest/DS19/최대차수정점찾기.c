/*
 * [문제] 가장 친구가 많은 정점 찾기 (Max Degree)
 *
 * [문제 설명]
 * 가장 많은 간선(친구)을 가진 정점의 번호와 그 차수를 출력하시오.
 * 차수가 같으면 번호가 작은 것을 출력한다.
 *
 * [입력 예시]
 * 4 3
 * 0 1
 * 0 2
 * 0 3
 *
 * [출력 예시]
 * 0 3      (0번 정점이 1,2,3과 연결되어 차수 3으로 최대)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 55

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer graph[MAX_VERTICES];

void insert(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
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

    int maxDegree = -1;
    int maxVertex = -1;

    for (int i = 0; i < N; i++) {
        int currentDegree = 0;
        for (nodePointer w = graph[i]; w; w = w->link) {
            currentDegree++;
        }
        if (currentDegree > maxDegree) {
            maxDegree = currentDegree;
            maxVertex = i;
        }
    }

    printf("%d %d\n", maxVertex, maxDegree);
    return 0;
}