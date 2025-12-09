/*
 * [문제 2]
 * Postfix expression의 명제식을 입력받아 이진트리를 구성하여
 * 중위순회(inorder traversal) 결과를 출력하고,
 * 명제식 변수(a, b, c)의 모든 진리값 조합(T/F)에 대한 결과를 출력하라.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

 // 교재 및 문제 요구사항에 맞춘 enum 및 struct 정의
typedef enum { NOT, AND, OR, true_val, false_val } logical; // true, false는 소문자 예약어 충돌 방지
typedef struct node* treePointer;
typedef struct node {
    treePointer leftChild;
    char var;         // 피연산자 문자 (a, b, c)
    logical data;     // 연산자 타입 (AND, OR, NOT 등)
    short int value;  // 계산된 진리값 (TRUE/FALSE)
    treePointer rightChild;
} tNode;

treePointer stack[MAX_STACK_SIZE];
int top = -1;

// 전역 변수로 현재 진리값 설정
int val_a, val_b, val_c;

void push(treePointer item) {
    stack[++top] = item;
}

treePointer pop() {
    return stack[top--];
}

// 새 노드 생성 헬퍼 함수
treePointer createNode(char var, logical data, treePointer left, treePointer right) {
    treePointer node = (treePointer)malloc(sizeof(tNode));
    node->var = var;
    node->data = data;
    node->leftChild = left;
    node->rightChild = right;
    node->value = FALSE;
    return node;
}

// 후위 표기식을 이용한 트리 생성
treePointer createBinTree(char* postfix) {
    top = -1;
    int len = strlen(postfix);
    treePointer node, op1, op2;

    for (int i = 0; i < len; i++) {
        char symbol = postfix[i];

        if (symbol == '&') {
            op2 = pop();
            op1 = pop();
            node = createNode(' ', AND, op1, op2);
            push(node);
        }
        else if (symbol == '|') {
            op2 = pop();
            op1 = pop();
            node = createNode(' ', OR, op1, op2);
            push(node);
        }
        else if (symbol == '~') {
            op1 = pop();
            // NOT 연산자는 단항이므로 오른쪽 자식(또는 왼쪽) 하나만 가짐
            node = createNode(' ', NOT, NULL, op1); // 편의상 오른쪽에 배치
            push(node);
        }
        else { // 피연산자 (a, b, c)
            node = createNode(symbol, true_val, NULL, NULL); // data는 임시로 true_val
            push(node);
        }
    }
    return pop();
}

// 중위 순회 (수식 복원 출력용)
void inorder(treePointer ptr) {
    if (ptr) {
        if (ptr->data == NOT) printf("~"); // 전위 표기되는 연산자
        inorder(ptr->leftChild);
        if (ptr->data == AND) printf("&");
        if (ptr->data == OR) printf("|");
        if (ptr->var != ' ') printf("%c", ptr->var);
        inorder(ptr->rightChild);
    }
}

// 후위 순회를 이용한 수식 계산 (Evaluation)
void postorderEval(treePointer node) {
    if (node) {
        postorderEval(node->leftChild);
        postorderEval(node->rightChild);

        switch (node->data) {
        case NOT:
            node->value = !node->rightChild->value;
            break;
        case AND:
            node->value = node->leftChild->value && node->rightChild->value;
            break;
        case OR:
            node->value = node->leftChild->value || node->rightChild->value;
            break;
        default: // 피연산자
            if (node->var == 'a') node->value = val_a;
            else if (node->var == 'b') node->value = val_b;
            else if (node->var == 'c') node->value = val_c;
            break;
        }
    }
}

int main() {
    char postfix[100];
    FILE* fp = fopen("postfix.txt", "r");

    if (fp == NULL) {
        // 파일 없으면 1번 문제의 결과 예시 사용
        strcpy(postfix, "ab~&a~c&|"); // (a&~b)|(~a&c) 의 후위 표기 (예시 수정됨)
    }
    else {
        fscanf(fp, "%s", postfix);
        fclose(fp);
    }

    printf("************* satisfiability problem ***********\n");
    printf("Input string(postfix): %s\n", postfix);

    printf("creating binary tree for satisfiability algorithm...\n");
    treePointer root = createBinTree(postfix);

    printf("Inorder traversal      : ");
    inorder(root);
    printf("\n\n");

    printf("for all combinations of (a, b, c)....\n");

    // 000(FFF) 부터 111(TTT) 까지 8가지 경우의 수
    // 1 = TRUE(t), 0 = FALSE(f)
    for (int i = 7; i >= 0; i--) { // 예시 출력 순서(t,t,t -> f,f,f)에 맞춤
        val_a = (i >> 2) & 1;
        val_b = (i >> 1) & 1;
        val_c = (i >> 0) & 1;

        postorderEval(root);

        printf("(%c, %c, %c) is %s\n",
            val_a ? 't' : 'f',
            val_b ? 't' : 'f',
            val_c ? 't' : 'f',
            root->value ? "TRUE" : "FALSE");
    }

    return 0;
}