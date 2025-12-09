/*
 * [문제 1] Graph: DFS
 *
 * [문제 설명]
 * 입력 파일(input.txt)로부터 무방향 그래프 데이터를 읽어 인접 리스트를 구성하고,
 * 각 정점(0 ~ n-1)을 시작점으로 하는 DFS 결과를 출력하시오.
 *
 * [입력]
 * input.txt 파일 (첫 줄: 정점 수 N, 간선 수 M / 이후: 연결된 두 정점 u v)
 *
 * [출력]
 * 1. 구성된 인접 리스트 (Adjacency List)
 * 2. 각 정점을 시작으로 한 DFS 탐색 경로
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

// 인접 리스트 노드 구조체
typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer graph[MAX_VERTICES];
short int visited[MAX_VERTICES];
int n = 0; // 정점의 수

// 인접 리스트 삽입 (헤더의 앞부분에 삽입)
void insert(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
}

// DFS 알고리즘 (Program 6.1)
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

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (!fp) {
        fprintf(stderr, "input.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    int m; // 간선의 수
    fscanf(fp, "%d %d", &n, &m);

    // 그래프 초기화
    for (int i = 0; i < n; i++) graph[i] = NULL;

    // 간선 입력 및 인접 리스트 구성 (무방향 그래프이므로 양방향 연결)
    int u, v;
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%d %d", &u, &v);
        insert(u, v);
        insert(v, u);
    }
    fclose(fp);

    // 인접 리스트 출력
    printf("<<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        printf("graph[%d]: ", i);
        for (nodePointer w = graph[i]; w; w = w->link) {
            printf("%5d", w->vertex);
        }
        printf("\n");
    }

    // DFS 결과 출력
    printf("<<<<<<<<<<<<< Depth First Search >>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        // visited 배열 초기화
        for (int j = 0; j < n; j++) visited[j] = FALSE;
        
        printf("dfs<%d>:", i);
        dfs(i);
        printf("\n");
    }

    return 0;
}