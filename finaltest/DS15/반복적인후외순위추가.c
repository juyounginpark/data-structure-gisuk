/*
[변형 문제 4]
후위표현식으로부터 산술식 이진트리를 생성한 뒤,

(1) 반복문을 사용한 전위순회(iterative preorder)
(2) 반복문을 사용한 중위순회(iterative inorder)
(3) 반복문을 사용한 후위순회(iterative postorder)

를 모두 구현하여 출력하는 프로그램을 작성하라.
(스택은 treePointer 를 요소로 갖는 배열 스택을 사용한다.)

2024002779 김시연
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer stack[MAX_STACK_SIZE];
int top = -1;
char expr[81];

void push(treePointer item) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack Full\n");
        exit(1);
    }
    stack[++top] = item;
}

treePointer pop(void) {
    if (top == -1) return NULL;
    return stack[top--];
}

int stackEmpty(void) {
    return top == -1;
}

treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

treePointer createBinTree(void) {
    int i = 0;
    char symbol;
    top = -1;

    while ((symbol = expr[i]) != '\0') {
        if (symbol >= 'A' && symbol <= 'Z') {
            push(createNode(symbol));
        } else {
            treePointer op = createNode(symbol);
            op->rightChild = pop();
            op->leftChild  = pop();
            push(op);
        }
        i++;
    }
    return pop();
}

void iterInorder(treePointer root) {
    top = -1;
    treePointer cur = root;

    while (1) {
        while (cur) {
            push(cur);
            cur = cur->leftChild;
        }
        if (stackEmpty()) break;
        cur = pop();
        printf("%c", cur->data);
        cur = cur->rightChild;
    }
}

void iterPreorder(treePointer root) {
    top = -1;
    treePointer cur = root;

    while (1) {
        while (cur) {
            printf("%c", cur->data);
            push(cur);
            cur = cur->leftChild;
        }
        if (stackEmpty()) break;
        cur = pop();
        cur = cur->rightChild;
    }
}

// 두 번째 스택을 이용한 postorder
void iterPostorder(treePointer root) {
    if (!root) return;

    treePointer s1[MAX_STACK_SIZE];
    treePointer s2[MAX_STACK_SIZE];
    int t1 = -1, t2 = -1;

    s1[++t1] = root;

    while (t1 != -1) {
        treePointer node = s1[t1--];
        s2[++t2] = node;

        if (node->leftChild)  s1[++t1] = node->leftChild;
        if (node->rightChild) s1[++t1] = node->rightChild;
    }

    while (t2 != -1) {
        printf("%c", s2[t2--]->data);
    }
}

int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("input.txt open error\n");
        return 1;
    }

    if (fscanf(fp, "%80s", expr) != 1) {
        printf("no expression\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    treePointer root = createBinTree();

    printf("Iter Preorder : ");
    iterPreorder(root);
    printf("\n");

    printf("Iter Inorder  : ");
    iterInorder(root);
    printf("\n");

    printf("Iter Postorder: ");
    iterPostorder(root);
    printf("\n");

    return 0;
}
