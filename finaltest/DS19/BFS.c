/*
 * [문제 2] Graph: BFS
 *
 * [문제 설명]
 * 문제 1과 동일한 입력에 대해 BFS(너비 우선 탐색)를 수행하고 결과를 출력하시오.
 * 단, 큐(Queue)는 연결 리스트(Linked Queue)로 구현해야 한다.
 *
 * [입력]
 * input.txt 파일 (문제 1과 동일)
 *
 * [출력]
 * 1. 구성된 인접 리스트
 * 2. 각 정점을 시작으로 한 BFS 탐색 경로
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

// 큐 노드 정의
typedef struct qNode* queuePointer;
typedef struct qNode {
    int vertex;
    queuePointer link;
} tQNode;

nodePointer graph[MAX_VERTICES];
short int visited[MAX_VERTICES];
queuePointer front = NULL, rear = NULL; // 전역 큐 포인터
int n = 0;

// 큐 삽입 (Program 4.7 수정)
void addq(int item) {
    queuePointer temp = (queuePointer)malloc(sizeof(tQNode));
    temp->vertex = item;
    temp->link = NULL;
    if (front) rear->link = temp;
    else front = temp;
    rear = temp;
}

// 큐 삭제 (Program 4.8 수정)
int deleteq() {
    if (!front) return -1; // Queue Empty
    queuePointer temp = front;
    int item = temp->vertex;
    front = temp->link;
    free(temp);
    if (!front) rear = NULL; // 큐가 비면 rear도 초기화
    return item;
}

void insert(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
}

// BFS 알고리즘 (Program 6.2)
void bfs(int v) {
    nodePointer w;
    front = rear = NULL; // 큐 초기화
    
    printf("%5d", v);
    visited[v] = TRUE;
    addq(v);
    
    while (front) {
        v = deleteq();
        for (w = graph[v]; w; w = w->link) {
            if (!visited[w->vertex]) {
                printf("%5d", w->vertex);
                addq(w->vertex);
                visited[w->vertex] = TRUE;
            }
        }
    }
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (!fp) return 1;

    int m, u, v;
    fscanf(fp, "%d %d", &n, &m);

    for (int i = 0; i < n; i++) graph[i] = NULL;

    for (int i = 0; i < m; i++) {
        fscanf(fp, "%d %d", &u, &v);
        insert(u, v);
        insert(v, u);
    }
    fclose(fp);

    printf("<<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        printf("graph[%d]: ", i);
        for (nodePointer w = graph[i]; w; w = w->link) {
            printf("%5d", w->vertex);
        }
        printf("\n");
    }

    printf("<<<<<<<<<<<<<< Breadth First Search >>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) visited[j] = FALSE;
        printf("bfs<%d>:", i);
        bfs(i);
        printf("\n");
    }

    return 0;
}