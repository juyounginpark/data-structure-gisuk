/*
[변형 문제 2]
입력파일 input.txt 로부터 문자를 한 글자씩 읽어 완전이진트리를 생성하라.
(큐를 사용한 완전이진트리 삽입 알고리즘을 사용한다.)

(1) 중위순회(inorder), 전위순회(preorder), 후위순회(postorder)를 출력한다.
(2) 큐를 이용하여 레벨순회(level-order traversal)를 추가로 구현하고 출력한다.

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

int queueEmpty() {
    return front == rear;
}

int queueFull() {
    return (rear + 1) == MAX_QUEUE_SIZE;
}

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
        deleteq(); // 두 자식이 모두 찼으므로 큐에서 제거
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

// 레벨순회
void levelOrder(treePointer root) {
    if (root == NULL) return;

    int f = 0, r = 0;
    treePointer q[MAX_QUEUE_SIZE];
    q[++r] = root;

    while (f != r) {
        treePointer cur = q[++f];
        printf("%c", cur->data);
        if (cur->leftChild) q[++r] = cur->leftChild;
        if (cur->rightChild) q[++r] = cur->rightChild;
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

    printf("Inorder   : ");
    inorder(root);
    printf("\n");

    printf("Preorder  : ");
    preorder(root);
    printf("\n");

    printf("Postorder : ");
    postorder(root);
    printf("\n");

    printf("Levelorder: ");
    levelOrder(root);
    printf("\n");

    return 0;
}
