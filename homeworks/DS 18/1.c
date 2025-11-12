/*
2025002720
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* link;
} Node;

typedef struct {
    Node* head;
} Graph;

Graph* createGraph(int n);
void insertEdge(Graph* g, int u, int v, char type);
void printGraph(Graph* g, int n);
void freeGraph(Graph* g, int n);

int main(void) {
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) return 1;

    char type;
    int n, e;
    fscanf(fp, " %c %d %d", &type, &n, &e);

    Graph* g = createGraph(n);

    for (int i = 0; i < e; i++) {
        int u, v;
        fscanf(fp, "%d %d", &u, &v);
        insertEdge(g, u, v, type);
    }

    printf("<<<<<<<<<< Adjacency List >>>>>>>>>>>>\n");
    printGraph(g, n);

    fclose(fp);
    freeGraph(g, n);
    return 0;
}

Graph* createGraph(int n) {
    Graph* g = (Graph*)malloc(sizeof(Graph) * n);
    for (int i = 0; i < n; i++) g[i].head = NULL;
    return g;
}

void insertEdge(Graph* g, int u, int v, char type) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = g[u].head;
    g[u].head = newNode;

    if (type == 'u') {
        Node* newNode2 = (Node*)malloc(sizeof(Node));
        newNode2->vertex = u;
        newNode2->link = g[v].head;
        g[v].head = newNode2;
    }
}

void printGraph(Graph* g, int n) {
    for (int i = 0; i < n; i++) {
        printf("adjList[%d] : ", i);
        Node* p = g[i].head;
        while (p != NULL) {
            printf("%d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}

void freeGraph(Graph* g, int n) {
    for (int i = 0; i < n; i++) {
        Node* p = g[i].head;
        while (p != NULL) {
            Node* temp = p;
            p = p->link;
            free(temp);
        }
    }
    free(g);
}

