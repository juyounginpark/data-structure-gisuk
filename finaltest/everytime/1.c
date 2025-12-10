/*문제 1] 학번, 이름, 성적 구조체 트리 (Level Order & Postorder)
핵심 요구사항:

학번, 이름, 성적을 포함한 구조체 정의

트리 구성 (학번 기준 이진 탐색 트리로 구현)

Level Order (레벨 순회): 큐(Queue) 자료구조 필요

Postorder (후위 순회): 재귀(Recursion) 활용*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE 100

// 1. 학생 정보를 담은 노드 구조체
typedef struct Node {
    int id;             // 학번
    char name[20];      // 이름
    double score;       // 성적
    struct Node* left;
    struct Node* right;
} Node;

// 큐 구조체 (Level Order용)
typedef struct {
    Node* items[MAX_QUEUE];
    int front, rear;
} Queue;

// 노드 생성 함수
Node* createNode(int id, char* name, double score) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->score = score;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 트리 삽입 (학번 기준 BST)
Node* insert(Node* root, int id, char* name, double score) {
    if (root == NULL) return createNode(id, name, score);
    if (id < root->id)
        root->left = insert(root->left, id, name, score);
    else if (id > root->id)
        root->right = insert(root->right, id, name, score);
    return root;
}

// --- 순회 알고리즘 ---

// 1. 후위 순회 (Postorder: Left -> Right -> Root)
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("[%d %s %.1f] ", root->id, root->name, root->score);
    }
}

// 큐 관련 함수
void initQueue(Queue* q) { q->front = q->rear = 0; }
void enqueue(Queue* q, Node* node) { q->items[q->rear++] = node; }
Node* dequeue(Queue* q) { return q->items[q->front++]; }
int isEmpty(Queue* q) { return q->front == q->rear; }

// 2. 레벨 순회 (Level Order)
void levelOrder(Node* root) {
    if (root == NULL) return;
    
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node* current = dequeue(&q);
        printf("[%d %s %.1f] ", current->id, current->name, current->score);

        if (current->left != NULL) enqueue(&q, current->left);
        if (current->right != NULL) enqueue(&q, current->right);
    }
}

int main() {
    Node* root = NULL;
    
    // 데이터 입력
    root = insert(root, 2023001, "Kim", 90.5);
    root = insert(root, 2023005, "Lee", 88.0);
    root = insert(root, 2023003, "Park", 95.0);
    root = insert(root, 2023002, "Choi", 77.5);
    root = insert(root, 2023004, "Jung", 82.0);

    printf("1. Postorder Traversal (후위 순회):\n");
    postorder(root);
    printf("\n\n");

    printf("2. Level Order Traversal (레벨 순회):\n");
    levelOrder(root);
    printf("\n");

    return 0;
}