/*문제 2] 방향성 그래프의 Inverse Adjacency List 출력
핵심 요구사항:

방향 그래프(Directed Graph)를 인접 리스트(Adjacency List)로 표현

이를 뒤집은(Edge 방향을 반대로 바꾼) 역인접 리스트 생성 및 출력*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

// 인접 리스트의 노드 정의
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 그래프 구조체
typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX_VERTICES];
} Graph;

// 그래프 초기화
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    return graph;
}

// 간선 추가 (src -> dest)
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src]; // 리스트의 맨 앞에 추가
    graph->adjLists[src] = newNode;
}

// 역인접 리스트 생성 함수 (핵심 로직)
Graph* createInverseGraph(Graph* srcGraph) {
    int v = srcGraph->numVertices;
    Graph* invGraph = createGraph(v);

    for (int i = 0; i < v; i++) {
        Node* temp = srcGraph->adjLists[i];
        while (temp) {
            // 원본: i -> temp->vertex
            // 역본: temp->vertex -> i (방향 뒤집어서 추가)
            addEdge(invGraph, temp->vertex, i);
            temp = temp->next;
        }
    }
    return invGraph;
}

// 리스트 출력
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        printf("Vertex %d: ", i);
        while (temp) {
            printf("-> %d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int vertices = 5;
    Graph* graph = createGraph(vertices);

    // 그래프 구성 (0->1, 0->2, 1->2, 2->4, 3->0, 4->3)
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 0);
    addEdge(graph, 4, 3);

    printf("[Original Adjacency List]\n");
    printGraph(graph);

    // 역인접 리스트 생성
    Graph* inverseGraph = createInverseGraph(graph);

    printf("\n[Inverse Adjacency List]\n");
    printGraph(inverseGraph);

    return 0;
}