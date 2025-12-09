/*
 * [문제 1] Connected Components
 *
 * [문제 설명]
 * 입력된 무방향 그래프의 인접 리스트를 구성하고, 연결 성분(Connected Component)들을 찾아 출력하시오.
 *
 * [입력 예시 (input.txt)]
 * 8 7
 * 0 1
 * 0 2
 * 1 3
 * 2 3
 * 4 5
 * 5 6
 * 6 7
 *
 * [출력 예시]
 * <<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>
 * graph[0]: 2 1
 * ...
 * <<<<<<<<<<<<< Connected Components >>>>>>>>>>
 * connected component 1: 0 2 3 1
 * connected component 2: 4 5 6 7
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

nodePointer graph[MAX_VERTICES];
int visited[MAX_VERTICES];
int n; // 정점의 수

// 인접 리스트 삽입
void insert(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
}

// DFS 탐색
void dfs(int v) {
    nodePointer w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex);
        }
    }
}

// 연결 성분 찾기 (Program 6.3)
void connected() {
    int i;
    int count = 1;
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("connected component %d:", count++);
            dfs(i);
            printf("\n");
        }
    }
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (!fp) return 1;

    int m, u, v;
    fscanf(fp, "%d %d", &n, &m); // 정점 수, 간선 수 입력

    // 초기화
    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
        visited[i] = FALSE;
    }

    // 그래프 구성
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%d %d", &u, &v);
        insert(u, v);
        insert(v, u); // 무방향 그래프
    }
    fclose(fp);

    // 인접 리스트 출력
    printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        printf("graph[%d]: ", i);
        for (nodePointer w = graph[i]; w; w = w->link) {
            printf("%5d", w->vertex);
        }
        printf("\n");
    }

    // 연결 성분 출력
    printf("<<<<<<<<<<<<< Connected Components >>>>>>>>>>\n");
    connected();

    return 0;
}