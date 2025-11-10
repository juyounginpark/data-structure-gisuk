/*
2025002720
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int iType;
typedef struct {
    int key;
    iType item;
} element;

typedef struct node *treePointer;
typedef struct node {
    element data;
    treePointer leftChild, rightChild;
} node;

treePointer root = NULL;

treePointer modifiedSearch(treePointer ptr, int k) {
    if (ptr == NULL) return NULL;
    treePointer parent = NULL;
    while (ptr != NULL) {
        if (k == ptr->data.key) return NULL;
        parent = ptr;
        if (k < ptr->data.key)
            ptr = ptr->leftChild;
        else
            ptr = ptr->rightChild;
    }
    return parent;
}

void insert(treePointer *node, element item) {
    treePointer ptr, temp = modifiedSearch(*node, item.key);
    ptr = (treePointer)malloc(sizeof(*ptr));
    ptr->data = item;
    ptr->leftChild = ptr->rightChild = NULL;
    if (*node == NULL)
        *node = ptr;
    else if (temp == NULL)
        return;
    else if (item.key < temp->data.key)
        temp->leftChild = ptr;
    else
        temp->rightChild = ptr;
}

treePointer search(treePointer node, int k) {
    if (node == NULL) return NULL;
    if (k == node->data.key) return node;
    if (k < node->data.key) return search(node->leftChild, k);
    return search(node->rightChild, k);
}

void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data.key);
        inorder(ptr->rightChild);
    }
}

int main() {
    int seed, n;
    printf("random number generation (1 ~ 500)\n");
    printf("the number of nodes in BST (less than and equal to 50) : ");
    scanf("%d", &n);
    printf("seed : ");
    scanf("%d", &seed);
    srand(seed);

    printf("\ncreating a BST from random numbers\n");
    for (int i = 0; i < n; i++) {
        element e;
        e.key = rand() % 500 + 1;
        e.item = e.key;
        insert(&root, e);
    }

    int key;
    printf("the key to search : ");
    scanf("%d", &key);

    treePointer found = search(root, key);
    if (found)
        printf("the element's item is %d\n", found->data.item);
    else
        printf("there is no such an element\n");

    printf("\ninorder traversal of the BST shows the sorted sequence\n");
    inorder(root);

    return 0;
}
