/*
2025002720
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* link;
} Node;

typedef struct Graph {
    int n;
    Node* adjList[MAX_VERTICES];
} Graph;

int visited[MAX_VERTICES];

void initGraph(Graph* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        g->adjList[i] = NULL;
    }
}

void insertEdge(Graph* g, int v1, int v2) {
    Node* node1 = (Node*)malloc(sizeof(Node));
    node1->vertex = v2;
    node1->link = g->adjList[v1];
    g->adjList[v1] = node1;

    Node* node2 = (Node*)malloc(sizeof(Node));
    node2->vertex = v1;
    node2->link = g->adjList[v2];
    g->adjList[v2] = node2;
}

void printAdjList(Graph* g) {
    printf("<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>\n");
    for (int i = 0; i < g->n; i++) {
        printf("graph[%d] :\t", i);
        Node* temp = g->adjList[i];
        while (temp != NULL) {
            printf("%d\t", temp->vertex);
            temp = temp->link;
        }
        printf("\n");
    }
    printf("\n");
}

void dfs(Graph* g, int v) {
    Node* w;
    visited[v] = 1;
    printf("%d\t", v);
    
    for (w = g->adjList[v]; w != NULL; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(g, w->vertex);
        }
    }
}

void performDFS(Graph* g) {
    printf("<<<<<<<<<<<< Depth First Search >>>>>>>>>>\n");
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            visited[j] = 0;
        }
        printf("dfs(%d) :\t", i);
        dfs(g, i);
        printf("\n");
    }
}

int main() {
    Graph g;
    int n, m;
    FILE* fp = fopen("input.txt", "r");
    
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    fscanf(fp, "%d %d", &n, &m);
    initGraph(&g, n);

    for (int i = 0; i < m; i++) {
        int v1, v2;
        fscanf(fp, "%d %d", &v1, &v2);
        insertEdge(&g, v1, v2);
    }
    
    fclose(fp);

    printAdjList(&g);
    performDFS(&g);

    return 0;
}

