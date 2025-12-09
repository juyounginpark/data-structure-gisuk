/*
[변형 문제 3]
입력파일 input.txt 에 저장된 문자들을 이용하여 큐를 사용한 완전이진트리를 생성하라.

(1) 이진트리를 중위순회하여 노드를 출력한다.
(2) 자식이 없는 리프(leaf) 노드의 개수를 계산하여 출력한다.

2024002779 김시연
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer root = NULL;
treePointer queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

int queueEmpty() { return front == rear; }
int queueFull() { return (rear + 1) == MAX_QUEUE_SIZE; }

void addq(treePointer item) {
    if (queueFull()) {
        printf("Queue Full\n");
        exit(1);
    }
    queue[++rear] = item;
}

treePointer deleteq() {
    if (queueEmpty()) {
        printf("Queue Empty\n");
        return NULL;
    }
    return queue[++front];
}

treePointer getFront() {
    if (queueEmpty()) return NULL;
    return queue[front + 1];
}

treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

void insert(treePointer *pRoot, treePointer pNode) {
    if (*pRoot == NULL) {
        *pRoot = pNode;
        addq(pNode);
        return;
    }

    treePointer frontNode = getFront();

    if (frontNode->leftChild == NULL) {
        frontNode->leftChild = pNode;
    }
    else if (frontNode->rightChild == NULL) {
        frontNode->rightChild = pNode;
        deleteq();
    }

    addq(pNode);
}

treePointer createCompBinTree(FILE *fp) {
    char data;
    treePointer pNode;
    while (fscanf(fp, "%c", &data) != EOF) {
        if (data == '\n' || data == ' ') continue;
        pNode = createNode(data);
        insert(&root, pNode);
    }
    return root;
}

void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

// 리프 노드 개수 계산
int countLeaves(treePointer ptr) {
    if (ptr == NULL) return 0;
    if (ptr->leftChild == NULL && ptr->rightChild == NULL) return 1;
    return countLeaves(ptr->leftChild) + countLeaves(ptr->rightChild);
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("input.txt open error\n");
        return 1;
    }
    root = createCompBinTree(fp);
    fclose(fp);

    printf("Inorder : ");
    inorder(root);
    printf("\n");

    printf("Leaf count = %d\n", countLeaves(root));

    return 0;
}
