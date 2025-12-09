/*
[변형 문제 1]
피연산자가 한 자리 숫자(0~9)인 후위표현식을 입력받아 산술식 이진트리를 생성한 뒤,
해당 식의 값을 계산하여 출력하는 프로그램을 작성하라.

예)
입력 (input.txt) : 23/4*5+
의미            : ( (2 / 3) * 4 ) + 5

(1) 후위표현식으로부터 이진트리를 생성한다.
(2) 재귀 함수를 이용하여 식의 값을 계산한다(정수 연산, / 는 정수 나눗셈).
(3) 계산 결과를 출력한다.

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

treePointer createBinTree(void) {
    int i = 0;
    char symbol;
    top = -1;

    while ((symbol = expr[i]) != '\0') {
        if (symbol >= '0' && symbol <= '9') {   // 숫자(피연산자)
            push(createNode(symbol));
        } else {                                // 연산자
            treePointer opNode = createNode(symbol);
            opNode->rightChild = pop();
            opNode->leftChild  = pop();
            push(opNode);
        }
        i++;
    }
    return pop();
}

// 재귀 평가 함수
int eval(treePointer ptr) {
    if (!ptr) return 0;

    // 리프 노드 : 숫자
    if (!ptr->leftChild && !ptr->rightChild)
        return ptr->data - '0';

    int leftVal  = eval(ptr->leftChild);
    int rightVal = eval(ptr->rightChild);

    switch (ptr->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
        case '%': return leftVal % rightVal;
        default : return 0;
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
    int result = eval(root);

    printf("Expression = %s\n", expr);
    printf("Value      = %d\n", result);

    return 0;
}
