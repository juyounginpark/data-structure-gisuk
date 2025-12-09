/*
[변형 문제 1]
다음 그림과 같은 이진트리를 생성하라.
        A
       / \
      B   C
     / \
    D   E

(1) 위 이진트리를 생성한다.
(2) 중위순회, 전위순회, 후위순회를 차례로 출력한다.
(3) 전체 노드의 개수와 트리의 높이(루트 레벨을 1로 가정)를 출력한다.

2024002779 김시연
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer root = NULL;

treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

treePointer createBinTree() {
    treePointer A = createNode('A');
    treePointer B = createNode('B');
    treePointer C = createNode('C');
    treePointer D = createNode('D');
    treePointer E = createNode('E');

    A->leftChild = B;
    A->rightChild = C;
    B->leftChild = D;
    B->rightChild = E;

    return A;
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

// 노드 수 계산
int countNodes(treePointer ptr) {
    if (ptr == NULL) return 0;
    return 1 + countNodes(ptr->leftChild) + countNodes(ptr->rightChild);
}

// 트리 높이 계산
int height(treePointer ptr) {
    if (ptr == NULL) return 0;
    int lh = height(ptr->leftChild);
    int rh = height(ptr->rightChild);
    return (lh > rh ? lh : rh) + 1;
}

int main() {
    root = createBinTree();

    printf("Inorder  : ");
    inorder(root);
    printf("\n");

    printf("Preorder : ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("Node count = %d\n", countNodes(root));
    printf("Height    = %d\n", height(root));

    return 0;
}
