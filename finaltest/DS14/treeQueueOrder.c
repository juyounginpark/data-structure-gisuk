/*
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

// 큐가 비었는지 확인
int queueEmpty() {
    return front == rear;
}

// 큐가 가득 찼는지 확인
int queueFull() {
    return (rear + 1) % MAX_QUEUE_SIZE == front;
}

// 큐 삽입
void addq(treePointer item) {
    if (queueFull()) {
        printf("Queue Full\n");
        exit(1);
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear] = item;
}

// 큐 삭제
treePointer deleteq() {
    if (queueEmpty()) {
        printf("Queue Empty\n");
        return NULL;
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

// front 항목 반환(삭제 X)
treePointer getFront() {
    if (queueEmpty()) return NULL;
    return queue[(front + 1) % MAX_QUEUE_SIZE];
}

// 노드 생성
treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

// 완전이진트리 삽입
void insert(treePointer *pRoot, treePointer pNode) {
    if (*pRoot == NULL) {       // 첫 노드라면 루트로 설정
        *pRoot = pNode;
        addq(pNode);
        return;
    }

    treePointer frontNode = getFront();

    if (frontNode->leftChild == NULL) {       // 왼쪽 자식이 비어 있다면
        frontNode->leftChild = pNode;
    }
    else if (frontNode->rightChild == NULL) { // 오른쪽 자식이 비어 있다면
        frontNode->rightChild = pNode;
        deleteq();                            // 해당 노드의 두 자식이 찼으므로 큐에서 제거
    }

    addq(pNode); // 새 노드는 항상 큐에 추가
}

// 완전이진트리 생성
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

// 중위순회
void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

// 전위순회
void preorder(treePointer ptr) {
    if (ptr) {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

// 후위순회
void postorder(treePointer ptr) {
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
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

    printf("Preorder : ");
    preorder(root);
    printf("\n");

    printf("Postorder : ");
    postorder(root);
    printf("\n");

    return 0;
}
