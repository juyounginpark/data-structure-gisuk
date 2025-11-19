/*  
    2025002720 박주영
   본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0

typedef struct Node {
    int vertex;
    struct Node* link;
} Node;

Node* graph[MAX_VERTICES];
int visited[MAX_VERTICES];
int n;

void insert_edge(int u, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = v;
    node->link = graph[u];
    graph[u] = node;
}

void dfs(int v) {
    Node* w;
    visited[v] = TRUE;
    printf("%d ", v);
    for (w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex);
        }
    }
}

void connected(void) {
    int i;
    int count = 1;
    printf("\n<<<<<<<<<<<<< Connected Components >>>>>>>>>>>>>\n");
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("connected component %d : ", count++);
            dfs(i);
            printf("\n");
        }
    }
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("file open error\n");
        return 0;
    }

    int m; 
    int u, v;

    if (fscanf(fp, "%d %d", &n, &m) != 2) {
        n = 8; 
        rewind(fp); 
    }

    for(int i=0; i<n; i++) {
        graph[i] = NULL;
        visited[i] = FALSE;
    }

    while (fscanf(fp, "%d %d", &u, &v) != EOF) {
        insert_edge(u, v);
        insert_edge(v, u);
    }
    fclose(fp);

    printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        printf("graph[%d] : ", i);
        for (Node* w = graph[i]; w; w = w->link) {
            printf("%d ", w->vertex);
        }
        printf("\n");
    }

    connected();

    return 0;
}