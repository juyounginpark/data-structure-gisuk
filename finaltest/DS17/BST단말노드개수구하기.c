#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
typedef struct node* treePointer;
typedef struct node {
    int key;
    treePointer leftChild, rightChild;
} tNode;

// [단말 노드 개수 구하는 함수 (핵심)]
int countLeaf(treePointer ptr) {
    // 1. 기저 조건: 노드가 NULL이면 개수는 0
    if (ptr == NULL) return 0;
    
    // 2. 단말 노드 확인 조건: 왼쪽 자식과 오른쪽 자식이 모두 NULL인 경우
    if (ptr->leftChild == NULL && ptr->rightChild == NULL) {
        return 1; // 단말 노드이므로 1 반환
    }
    
    // 3. 재귀 호출: 왼쪽 서브트리의 단말 노드 수 + 오른쪽 서브트리의 단말 노드 수
    return countLeaf(ptr->leftChild) + countLeaf(ptr->rightChild);
}

// (테스트용) BST 삽입 함수
void insert(treePointer* root, int k) {
    if (!(*root)) { // 자리가 비었으면 노드 생성
        *root = (treePointer)malloc(sizeof(tNode));
        (*root)->key = k;
        (*root)->leftChild = (*root)->rightChild = NULL;
        return;
    }
    // 키값 비교 후 재귀적 삽입
    if (k < (*root)->key) insert(&((*root)->leftChild), k);
    else if (k > (*root)->key) insert(&((*root)->rightChild), k);
}

int main() {
    treePointer root = NULL;
    // 트리 생성: 50, 30, 20, 40, 70
    //       50
    //      /  \
    //    30    70
    //   /  \
    // 20    40
    // 단말 노드는 20, 40, 70 -> 총 3개여야 함
    int data[] = { 50, 30, 20, 40, 70 };
    for(int i=0; i<5; i++) insert(&root, data[i]);
    
    printf("Count of Leaf Nodes: %d\n", countLeaf(root));
    
    return 0;
}