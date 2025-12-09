/*
[변형 문제 4]
하나의 이진트리에 대해 중위순회(inorder) 결과와 전위순회(preorder) 결과가
다음과 같이 주어진다고 하자.

예) inorder  : DBEACF
    preorder : ABDECF

(1) 중위순회와 전위순회 결과 문자열을 입력으로 받아 이진트리를 복원한다.
(2) 복원된 이진트리에 대해 후위순회(postorder) 결과를 출력한다.

입력 예)
DBEACF
ABDECF

출력 예)
Postorder : DEBFCA

2024002779 김시연
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

// inorder[inStart..inEnd], preorder[preStart..preEnd]
treePointer buildTree(char *inorder, char *preorder,
                      int inStart, int inEnd,
                      int *preIndex) {
    if (inStart > inEnd) return NULL;

    char rootData = preorder[*preIndex];
    (*preIndex)++;

    treePointer root = createNode(rootData);

    // 리프 노드
    if (inStart == inEnd) return root;

    // inorder에서 루트 위치 찾기
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (inorder[inIndex] == rootData) break;
    }

    root->leftChild  = buildTree(inorder, preorder, inStart, inIndex - 1, preIndex);
    root->rightChild = buildTree(inorder, preorder, inIndex + 1, inEnd, preIndex);

    return root;
}

void postorder(treePointer ptr) {
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
}

int main() {
    char inorder[101], preorder[101];

    if (scanf("%s", inorder) != 1) return 0;
    if (scanf("%s", preorder) != 1) return 0;

    int n = (int)strlen(inorder);
    int preIndex = 0;

    treePointer root = buildTree(inorder, preorder, 0, n - 1, &preIndex);

    printf("Postorder : ");
    postorder(root);
    printf("\n");

    return 0;
}
