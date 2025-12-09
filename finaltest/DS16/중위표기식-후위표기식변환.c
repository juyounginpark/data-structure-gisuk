/*
 * [문제 2] 충족 가능 문제 (Satisfiability Problem)
 * * [문제 설명]
 * postfix expression의 명제식을 입력받아 이진트리를 구성하여 
 * 중위순회(inorder traversal)한 결과를 출력한 후,
 * 변수(a, b, c)의 모든 진리값 조합(8가지)에 대한 결과를 출력하라.
 *
 * [입력]
 * 첫째 줄에 후위표기식(postfix expression)이 주어진다. (예: ab~&a~c&|)
 * - 피연산자: a, b, c
 * - 연산자: &(AND), |(OR), ~(NOT)
 *
 * [출력]
 * 1. Inorder traversal 결과
 * 2. (a, b, c)의 모든 T/F 조합에 따른 연산 결과
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

// PDF 명세에 따른 열거형 및 구조체 정의
// 주의: C++ 컴파일러 사용 시 true, false가 예약어이므로 .c로 컴파일하거나 이름을 변경해야 함
typedef enum { NOT, AND, OR, TRUE_NODE, FALSE_NODE } logical; 

typedef struct node *treePointer;
typedef struct node {
    treePointer leftChild;
    char var;           // 피연산자 문자 (a, b, c)
    logical data;       // 연산자 종류 (AND, OR, NOT 등)
    short int value;    // 평가된 진리값 (TRUE/FALSE)
    treePointer rightChild;
} tNode;

// 전역 변수: 현재 평가 중인 a, b, c의 진리값
int val_a, val_b, val_c;

// 트리 생성을 위한 스택
treePointer stack[MAX_STACK_SIZE];
int top = -1;

void push(treePointer item) {
    if (top >= MAX_STACK_SIZE - 1) return;
    stack[++top] = item;
}

treePointer pop() {
    if (top == -1) return NULL;
    return stack[top--];
}

// 노드 생성 헬퍼 함수
treePointer createNode(char v, logical d, treePointer l, treePointer r) {
    treePointer node = (treePointer)malloc(sizeof(tNode));
    node->var = v;
    node->data = d;
    node->value = 0;
    node->leftChild = l;
    node->rightChild = r;
    return node;
}

// 후위 표기식을 이진 트리로 변환
treePointer createBinTree(char *expr) {
    int len = strlen(expr);
    top = -1; // 스택 초기화

    for (int i = 0; i < len; i++) {
        char symbol = expr[i];

        if (symbol == '&') {
            treePointer right = pop();
            treePointer left = pop();
            push(createNode(0, AND, left, right));
        }
        else if (symbol == '|') {
            treePointer right = pop();
            treePointer left = pop();
            push(createNode(0, OR, left, right));
        }
        else if (symbol == '~') {
            treePointer right = pop(); // 단항 연산자 NOT
            push(createNode(0, NOT, NULL, right));
        }
        else {
            // 피연산자 (Operand)
            push(createNode(symbol, TRUE_NODE, NULL, NULL)); 
        }
    }
    return pop(); // 루트 노드 반환
}

// 트리 후위 순회하며 평가 (Postorder Evaluation)
void postorderEval(treePointer node) {
    if (!node) return;

    postorderEval(node->leftChild);
    postorderEval(node->rightChild);

    switch (node->data) {
    case AND:
        node->value = node->leftChild->value && node->rightChild->value;
        break;
    case OR:
        node->value = node->leftChild->value || node->rightChild->value;
        break;
    case NOT:
        node->value = !node->rightChild->value;
        break;
    default: 
        // 피연산자인 경우 전역 변수 값 매핑
        if (node->var == 'a') node->value = val_a;
        else if (node->var == 'b') node->value = val_b;
        else if (node->var == 'c') node->value = val_c;
        break;
    }
}

// 중위 순회 (Inorder Traversal) 출력
void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        if (ptr->data == AND) printf("&");
        else if (ptr->data == OR) printf("|");
        else if (ptr->data == NOT) printf("~");
        else printf("%c", ptr->var);
        inorder(ptr->rightChild);
    }
}

int main() {
    char expr[100];
    
    // 파일 입력을 원칙으로 하나, 실행 편의를 위해 표준 입력 사용 가능
    // FILE *fp = fopen("postfix.txt", "r"); fscanf(fp, "%s", expr); fclose(fp);
    
    printf("Input Postfix Expression (ex: ab~&a~c&|): ");
    scanf("%s", expr);

    printf("\nCreating binary tree for satisfiability algorithm...\n");
    treePointer root = createBinTree(expr);

    printf("Inorder traversal : ");
    inorder(root);
    printf("\n\nfor all combinations of (a, b, c)...\n");

    // 000(0) 부터 111(7) 까지 모든 조합 루프
    for (int i = 0; i < 8; i++) {
        // 비트 연산으로 T/F 설정 (4: a, 2: b, 1: c)
        // 문제 예시 순서(t,t,t -> f,f,f)에 맞추기 위해 로직 조정 필요할 수 있음
        // 여기서는 일반적인 2진수 순서로 작성
        val_a = (i & 4) ? FALSE : TRUE; 
        val_b = (i & 2) ? FALSE : TRUE; 
        val_c = (i & 1) ? FALSE : TRUE;

        postorderEval(root);

        printf("(%c, %c, %c) is %s\n", 
            val_a ? 't' : 'f', 
            val_b ? 't' : 'f', 
            val_c ? 't' : 'f', 
            root->value ? "TRUE" : "FALSE");
    }

    return 0;
}