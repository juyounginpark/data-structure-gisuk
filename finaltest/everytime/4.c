/*[문제 1] 후위연산식 → 이진 트리 변환 및 순회
업로드해주신 이미지(image_233ee4.png 또는 image_2346bc.png)에 있는 3가지 문제에 대한 정답 코드를 각각 작성해 드립니다.

이 이미지는 1. 후위연산식 트리 변환, 2. 최소 히프(Min Heap), 3. 해싱(Chaining & String Key) 문제를 포함하고 있습니다.

[문제 1] 후위연산식 → 이진 트리 변환 및 순회
요구사항: 후위표기식을 입력받아 이진 트리를 구성하고, 비재귀(Iterative) 방식으로 중위/전위 순회 및 레벨 순회를 수행하시오*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct TreeNode {
    char data;
    struct TreeNode *left, *right;
} TreeNode;

// --- 스택 (트리 생성 및 비재귀 순회용) ---
TreeNode* stack[MAX_SIZE];
int top = -1;

void push(TreeNode* node) { stack[++top] = node; }
TreeNode* pop() { return (top == -1) ? NULL : stack[top--]; }
int isStackEmpty() { return top == -1; }

// --- 큐 (레벨 순회용) ---
TreeNode* queue[MAX_SIZE];
int front = 0, rear = 0;

void enqueue(TreeNode* node) { queue[rear++] = node; }
TreeNode* dequeue() { return queue[front++]; }
int isQueueEmpty() { return front == rear; }

// 노드 생성
TreeNode* createNode(char data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 1. 후위표기식 -> 수식 트리 변환
TreeNode* buildTree(char* postfix) {
    int len = strlen(postfix);
    for (int i = 0; i < len; i++) {
        char ch = postfix[i];
        TreeNode* node = createNode(ch);
        
        // 피연산자(숫자나 문자)
        if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            push(node);
        } else { // 연산자
            node->right = pop();
            node->left = pop();
            push(node);
        }
    }
    return pop(); // 루트 반환
}

// 2. 비재귀 전위 순회 (Iterative Preorder)
void iterativePreorder(TreeNode* root) {
    if (root == NULL) return;
    top = -1; // 스택 초기화
    push(root);
    while (!isStackEmpty()) {
        TreeNode* node = pop();
        printf("%c ", node->data);
        if (node->right) push(node->right);
        if (node->left) push(node->left);
    }
}

// 3. 비재귀 중위 순회 (Iterative Inorder)
void iterativeInorder(TreeNode* root) {
    top = -1; // 스택 초기화
    TreeNode* curr = root;
    while (curr != NULL || !isStackEmpty()) {
        while (curr != NULL) {
            push(curr);
            curr = curr->left;
        }
        curr = pop();
        printf("%c ", curr->data);
        curr = curr->right;
    }
}

// 4. 레벨 순회 (Level Order)
void levelOrder(TreeNode* root) {
    if (root == NULL) return;
    front = rear = 0; // 큐 초기화
    enqueue(root);
    while (!isQueueEmpty()) {
        TreeNode* node = dequeue();
        printf("%c ", node->data);
        if (node->left) enqueue(node->left);
        if (node->right) enqueue(node->right);
    }
}

int main() {
    char postfix[] = "ab*c+"; // 예시: a * b + c
    printf("Postfix Expression: %s\n", postfix);

    TreeNode* root = buildTree(postfix);

    printf("Iterative Preorder : ");
    iterativePreorder(root);
    printf("\n");

    printf("Iterative Inorder  : ");
    iterativeInorder(root);
    printf("\n");

    printf("Level Order        : ");
    levelOrder(root);
    printf("\n");

    return 0;
}