#include <stdio.h>
#include <stdlib.h>


typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
}node;

treePointer root;

treePointer CreateNewNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(treePointer));
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode; 
}

void inorder(treePointer ptr) {
    //중위순회
    if(ptr) {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr) {
    //전위순회
    if(ptr) {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr) {
    if(ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
}

int main() {
    treePointer A = CreateNewNode('A');
    treePointer B = CreateNewNode('B');
    treePointer C = CreateNewNode('C');
    treePointer D = CreateNewNode('D');
    treePointer E = CreateNewNode('E');

    A->leftChild = B;
    A->rightChild = C;
    B->leftChild = D;
    B->rightChild = E;

    //중위 순회
    inorder(A);
    puts("");
    //전위 순회
    preorder(A);
    puts("");
    //후위 순회
    postorder(A);
    puts("");

}
