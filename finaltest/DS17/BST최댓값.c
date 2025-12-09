#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
    int key;
    treePointer leftChild, rightChild;
} tNode;

// [최댓값 탐색 함수 (핵심)]
// BST의 성질: 부모보다 큰 값은 항상 오른쪽에 위치합니다.
treePointer findMax(treePointer tree) {
    // 1. 트리가 비어있으면 NULL 반환
    if (tree == NULL) return NULL;
    
    // 2. 오른쪽 자식이 없을 때까지 계속 오른쪽으로 이동 (반복문)
    while (tree->rightChild != NULL) {
        // 현재 노드를 오른쪽 자식으로 갱신
        tree = tree->rightChild;
    }
    
    // 3. 더 이상 오른쪽으로 갈 수 없다면, 현재 노드가 가장 큰 값임
    return tree;
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
    // 트리 생성: 50, 80, 70, 90
    //       50
    //         \
    //          80
    //         /  \
    //       70    90 (Max)
    int data[] = { 50, 80, 70, 90 };
    for(int i=0; i<4; i++) insert(&root, data[i]);
    
    treePointer maxNode = findMax(root);
    
    if (maxNode != NULL) {
        printf("Max Value in BST: %d\n", maxNode->key);
    } else {
        printf("Tree is empty.\n");
    }
    
    return 0;
}