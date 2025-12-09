/*
 * [문제] 특정 정점까지의 최단 거리
 *
 * [문제 설명]
 * 그래프와 시작 정점 S, 도착 정점 E가 주어질 때, S에서 E까지의 최단 거리(간선 개수)를 구하시오.
 * 도달할 수 없으면 -1을 출력한다.
 *
 * [입력 예시]
 * 5 5      (N=5, M=5)
 * 1 2
 * 1 3
 * 2 4
 * 4 5
 * 3 5
 * 1 5      (Start=1, End=5)
 *
 * [출력 예시]
 * 2        (1->3->5 가 최단 경로)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 55
#define MAX_QUEUE 100

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer graph[MAX_VERTICES];
int distance[MAX_VERTICES];
int queue[MAX_QUEUE];
int front = 0, rear = 0;

void insert(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
}

void bfs(int start, int target) {
    front = rear = 0;
    queue[rear++] = start;
    distance[start] = 0;

    while (front < rear) {
        int v = queue[front++];
        if (v == target) return;

        for (nodePointer w = graph[v]; w; w = w->link) {
            if (distance[w->vertex] == -1) { // 방문 안 함
                distance[w->vertex] = distance[v] + 1;
                queue[rear++] = w->vertex;
            }
        }
    }
}

int main() {
    int N, M, S, E;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        graph[i] = NULL;
        distance[i] = -1; // 거리 초기화
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        insert(u, v);
        insert(v, u);
    }

    scanf("%d %d", &S, &E);
    bfs(S, E);

    printf("%d\n", distance[E]);
    return 0;
}