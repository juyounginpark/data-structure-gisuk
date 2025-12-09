/*
 * [문제 2] 이진 탐색 트리 (Binary Search Tree)
 *
 * [문제 설명]
 * 난수를 생성하여 이진 탐색 트리를 구성하고, 특정 키를 탐색하며,
 * 중위 순회(Inorder Traversal)를 통해 정렬된 결과를 출력한다.
 *
 * [입력]
 * - 노드 개수 (n <= 50)
 * - Seed 값
 * - 탐색할 Key 값
 *
 * [출력]
 * - 생성된 트리의 정렬된 키 값 (중위 순회 결과)
 * - 탐색 결과 (Found / Not Found)
 *
 * [참고]
 * Program 5.15(Search), 5.17(Insert), modifiedSearch 알고리즘 적용 [cite: 264-310]
 */

#include <stdio.h>
#include <stdlib.h>

typedef int iType;
typedef struct {
    int key;
    iType item;
} element;

typedef struct node* treePointer;
typedef struct node {
    element data;
    treePointer leftChild, rightChild;
} tNode;

// BST 탐색 (Iterative) - Program 5.16 [cite: 274]
element* iterSearch(treePointer tree, int k) {
    while (tree) {
        if (k == tree->data.key) return &(tree->data);
        if (k < tree->data.key)
            tree = tree->leftChild;
        else
            tree = tree->rightChild;
    }
    return NULL;
}

// 수정된 탐색 (삽입 위치 찾기용) - modifiedSearch 
// k가 트리에 있으면 NULL 반환 (중복 방지), 없으면 마지막 도달 노드 반환
treePointer modifiedSearch(treePointer tree, int k) {
    treePointer lastNode = NULL;
    
    // 빈 트리인 경우
    if (!tree) return NULL;

    while (tree) {
        if (k == tree->data.key) return NULL; // 중복 키 존재
        
        lastNode = tree; // 현재 노드를 마지막 노드로 기록
        
        if (k < tree->data.key)
            tree = tree->leftChild;
        else
            tree = tree->rightChild;
    }
    return lastNode;
}

// BST 삽입 - Program 5.17 [cite: 284]
void insert(treePointer* node, int k, iType theItem) {
    treePointer ptr, temp = modifiedSearch(*node, k);

    // temp가 NULL이 아니거나(삽입 위치 찾음), 트리가 비어있는 경우(*node == NULL)
    // 단, modifiedSearch가 NULL을 반환했는데 *node가 NULL이 아니라면 중복 키인 경우임.
    if (temp || !(*node)) {
        // 중복 체크: 트리가 비어있지 않은데 temp가 NULL이면 중복 키이므로 삽입 안 함
        if (*node && !temp) return; 

        // 새 노드 할당
        ptr = (treePointer)malloc(sizeof(tNode));
        ptr->data.key = k;
        ptr->data.item = theItem;
        ptr->leftChild = ptr->rightChild = NULL;

        if (*node) { // 트리가 비어있지 않음 -> temp의 자식으로 연결
            if (k < temp->data.key) temp->leftChild = ptr;
            else temp->rightChild = ptr;
        }
        else { // 트리가 비어있음 -> 루트로 설정
            *node = ptr;
        }
    }
}

// 중위 순회 (정렬된 순서 출력) [cite: 253]
void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data.key);
        inorder(ptr->rightChild);
    }
}

int main() {
    int n, seed, keyVal;
    treePointer root = NULL;

    printf("random number generation (1~500)\n");
    printf("the number of nodes in BST (less than and equal to 50): ");
    scanf("%d", &n);
    printf("seed : ");
    scanf("%d", &seed);

    srand(seed);

    printf("\ncreating a BST from random numbers\n");
    
    // n개의 노드 삽입 (중복되지 않는 난수 n개가 채워질 때까지 반복하거나, 단순히 n번 시도)
    // 문제의 실행 순서 ④는 "과정을 n번 수행"이라고 했으므로 루프를 n번 돌립니다.
    // 다만 난수 특성상 중복이 발생할 수 있어 실제 노드 수는 n보다 적을 수 있습니다.
    for (int i = 0; i < n; i++) {
        int randKey = rand() % 500 + 1;
        insert(&root, randKey, randKey); // item도 key와 동일하게 저장
    }

    printf("the key to search : ");
    scanf("%d", &keyVal);

    element* result = iterSearch(root, keyVal);
    if (result) {
        printf("the element's item is %d\n", result->item);
    }
    else {
        printf("there is no such an element\n");
    }

    printf("\ninorder traversal of the BST shows the sorted sequence\n");
    inorder(root);
    printf("\n");

    return 0;
}