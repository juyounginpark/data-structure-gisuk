/*
2025002720
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
}node;
treePointer root;

treePointer createNode(char data);
treePointer createBinTree();
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main() {
    root = createBinTree();
    
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

treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

treePointer createBinTree() {
    treePointer nodeA = createNode('A');
    treePointer nodeB = createNode('B');
    treePointer nodeC = createNode('C');
    treePointer nodeD = createNode('D');
    treePointer nodeE = createNode('E');

    nodeA->leftChild = nodeB;
    nodeA->rightChild = nodeC;
    nodeB->leftChild = nodeD;
    nodeC->leftChild = nodeE;
    return nodeA;
}

void inorder(treePointer ptr)
{
    if(ptr) {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr)
{
    if(ptr) {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr)
{
    if(ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data); 
    }
}