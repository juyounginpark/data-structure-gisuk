/*
[자료구조응용 15번 1번 정답 코드]

후위표현식(postfix expression)을 입력받아 산술식 이진트리를 생성한 후,
중위표현식(infix), 전위표현식(prefix), 후위표현식(postfix)을 출력하는 프로그램.

- 입력 : input.txt 에 한 줄의 후위표현식 (예: AB/C*D*E+)
- 피연산자(operand) : 알파벳 한 글자
- 연산자(operator) : +, -, *, /, %

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

treePointer root = NULL;
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
    if (top == -1) {
        printf("Stack Empty\n");
        return NULL;
    }
    return stack[top--];
}

treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

// 후위표현식으로부터 이진트리 생성
treePointer createBinTree(void) {
    treePointer pNode;
    int i = 0;
    char symbol;

    top = -1;

    while ((symbol = expr[i]) != '\0') {
        if (symbol >= 'A' && symbol <= 'Z') {    // 피연산자
            pNode = createNode(symbol);
            push(pNode);
        }
        else {                                  // 연산자
            pNode = createNode(symbol);
            pNode->rightChild = pop();          // 오른쪽 피연산자
            pNode->leftChild  = pop();          // 왼쪽 피연산자
            push(pNode);
        }
        i++;
    }
    return pop();   // 스택의 마지막 노드가 루트
}

// 중위순회
void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

// 전위순회
void preorder(treePointer ptr) {
    if (ptr) {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

// 후위순회
void postorder(treePointer ptr) {
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
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

    root = createBinTree();

    printf("Infix   : ");
    inorder(root);
    printf("\n");

    printf("Prefix  : ");
    preorder(root);
    printf("\n");

    printf("Postfix : ");
    postorder(root);
    printf("\n");

    return 0;
}
