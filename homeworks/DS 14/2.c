/*
학번 이름
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

treePointer root;
treePointer queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int queueEmpty() {
    if (front == rear) {
        printf("Queue is empty\n");
        return 1;
    }
    return 0;
}

void queueFull() {
    printf("Queue is full\n");
    exit(1);
}

void addq(treePointer item) {
    if (rear == MAX_QUEUE_SIZE - 1) {
        queueFull();
    }
    queue[++rear] = item;
}

treePointer deleteq() {
    if (queueEmpty()) {
        return NULL;
    }
    return queue[++front];
}

treePointer getFront() {
    if (queueEmpty()) {
        return NULL;
    }
    return queue[front + 1];
}

treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

void insert(treePointer *pRoot, treePointer pNode) {
    if (*pRoot == NULL) {
        *pRoot = pNode;
        addq(pNode);
    }
    else {
        treePointer frontNode = getFront();
        
        if (frontNode->leftChild == NULL) {
            frontNode->leftChild = pNode;
            addq(pNode);
        }
        else if (frontNode->rightChild == NULL) {
            frontNode->rightChild = pNode;
            addq(pNode);
            deleteq();
        }
    }
}

treePointer createCompBinTree(FILE* fp) {
    treePointer pNode;
    char data;
    
    while (fscanf(fp, "%c ", &data) != EOF) {
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

void preorder(treePointer ptr) {
    if (ptr) {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr) {
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
}

int main() {
    FILE *fp;
    
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("File open error\n");
        return 1;
    }
    
    root = createCompBinTree(fp);
    fclose(fp);
    
    printf("inorder traversal\t:");
    inorder(root);
    printf("\n");
    
    printf("preorder traversal\t:");
    preorder(root);
    printf("\n");
    
    printf("postorder traversal\t:");
    postorder(root);
    printf("\n");
    
    return 0;
}