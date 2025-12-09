/*
[변형 문제 3]
후위표현식으로부터 산술식 이진트리를 만든 뒤,

(1) 전체 노드 수
(2) 피연산자(operand, 알파벳) 노드 수
(3) 연산자(operator, + - * / % ) 노드 수

를 각각 계산하여 출력하는 프로그램을 작성하라.

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

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

void countNodes(treePointer ptr, int *total, int *operands, int *operators) {
    if (!ptr) return;

    (*total)++;
    if (isOperator(ptr->data))
        (*operators)++;
    else
        (*operands)++;

    countNodes(ptr->leftChild, total, operands, operators);
    countNodes(ptr->rightChild, total, operands, operators);
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

    int total = 0, operands = 0, operators = 0;
    countNodes(root, &total, &operands, &operators);

    printf("Expression : %s\n", expr);
    printf("Total nodes      = %d\n", total);
    printf("Operand nodes    = %d\n", operands);
    printf("Operator nodes   = %d\n", operators);

    return 0;
}
