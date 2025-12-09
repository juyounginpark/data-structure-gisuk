/*
 * [문제 1] Graph: Adjacency List
 *
 * [문제 설명]
 * 파일 입력을 통해 무방향(u) 또는 방향(d) 그래프를 인접 리스트로 구성하고 출력하라.
 *
 * [입력 파일(input.txt) 형식]
 * 첫 줄: 그래프 종류(char), 정점 수(int), 간선 수(int)
 * 이후 줄: 간선 정보 (u v) - 정점 u와 v가 연결됨
 *
 * [출력]
 * 각 정점의 인접 리스트 상태 (Head -> Node -> Node ...)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

// 인접 리스트의 노드 구조체
typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

// 인접 리스트 배열 (각 정점의 헤드 포인터)
nodePointer adjLists[MAX_VERTICES];
int visited[MAX_VERTICES]; // (나중에 탐색 문제 등에 사용)

// 리스트의 맨 앞(헤드)에 노드를 삽입하는 함수
// 문제 조건: "항상 헤더노드가 가리키는 첫 노드로 입력되게 함"
void insertFront(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = adjLists[u];
    adjLists[u] = newNode;
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다. (input.txt 확인 필요)\n");
        return 1;
    }

    char type;
    int n, m; // n: 정점 수, m: 간선 수

    // 첫 줄 읽기 (예: u 4 6)
    fscanf(fp, "%c %d %d", &type, &n, &m);

    // 인접 리스트 초기화
    for (int i = 0; i < n; i++) {
        adjLists[i] = NULL;
    }

    // 간선 정보 읽기 및 리스트 구성
    int u, v;
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%d %d", &u, &v);
        
        // 방향 그래프(d): u -> v 만 연결
        if (type == 'd') {
            insertFront(u, v);
        }
        // 무방향 그래프(u): u -> v, v -> u 둘 다 연결
        else if (type == 'u') {
            insertFront(u, v);
            insertFront(v, u);
        }
    }
    fclose(fp);

    // 출력
    printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        printf("adjList[%d]: ", i);
        nodePointer curr = adjLists[i];
        while (curr != NULL) {
            printf("%d ", curr->vertex);
            curr = curr->link;
        }
        printf("\n");
    }

    return 0;
}