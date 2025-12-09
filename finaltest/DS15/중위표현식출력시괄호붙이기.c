/*
[변형 문제 2]
후위표현식을 이용해 산술식 이진트리를 생성한 뒤,

(1) 괄호를 이용한 중위표현식(infix with parentheses)을 출력한다.
    - 연산자 노드는 (left op right) 형태로 출력한다.
(2) 전위표현식(prefix)과 후위표현식(postfix)도 함께 출력한다.

예)
입력 : AB/C*D*E+
트리 중위표현식 : (((A/B)*D)*E)+?

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

// 괄호를 포함한 중위순회
void inorderWithParen(treePointer ptr) {
    if (!ptr) return;

    // 리프 노드는 그냥 출력
    if (!ptr->leftChild && !ptr->rightChild) {
        printf("%c", ptr->data);
        return;
    }
    // 연산자 노드: ( left op right )
    printf("(");
    inorderWithParen(ptr->leftChild);
    printf("%c", ptr->data);
    inorderWithParen(ptr->rightChild);
    printf(")");
}

void preorder(treePointer ptr) {
    if (!ptr) return;
    printf("%c", ptr->data);
    preorder(ptr->leftChild);
    preorder(ptr->rightChild);
}

void postorder(treePointer ptr) {
    if (!ptr) return;
    postorder(ptr->leftChild);
    postorder(ptr->rightChild);
    printf("%c", ptr->data);
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

    printf("Infix(with parentheses) : ");
    inorderWithParen(root);
    printf("\n");

    printf("Prefix                  : ");
    preorder(root);
    printf("\n");

    printf("Postfix                 : ");
    postorder(root);
    printf("\n");

    return 0;
}
