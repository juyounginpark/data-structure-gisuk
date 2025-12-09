#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
    int key;
    treePointer leftChild, rightChild;
} tNode;

// [트리 높이 구하는 함수 (핵심)]
int getHeight(treePointer ptr) {
    // 1. 기저 조건: 노드가 없으면 높이는 0
    if (ptr == NULL) return 0;
    
    // 2. 왼쪽 서브트리의 높이를 재귀적으로 구함
    int leftH = getHeight(ptr->leftChild);
    
    // 3. 오른쪽 서브트리의 높이를 재귀적으로 구함
    int rightH = getHeight(ptr->rightChild);
    
    // 4. 둘 중 더 큰 높이를 선택하고, 현재 노드(자기 자신)의 높이 1을 더함
    // 조건 연산자: (조건) ? 참일때 값 : 거짓일때 값
    return (leftH > rightH ? leftH : rightH) + 1;
}

// (테스트용) BST 삽입 함수
void insert(treePointer* root, int k) {
    if (!(*root)) {
        *root = (treePointer)malloc(sizeof(tNode));
        (*root)->key = k;
        (*root)->leftChild = (*root)->rightChild = NULL;
        return;
    }
    if (k < (*root)->key) insert(&((*root)->leftChild), k);
    else if (k > (*root)->key) insert(&((*root)->rightChild), k);
}

int main() {
    treePointer root = NULL;
    // 트리 생성
    //       50 (Height 1)
    //      /  
    //    30 (Height 2)
    //   /  
    // 20 (Height 3)
    int data[] = { 50, 30, 20 };
    for(int i=0; i<3; i++) insert(&root, data[i]);
    
    printf("Height of Tree: %d\n", getHeight(root));
    
    return 0;
}