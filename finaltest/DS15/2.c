/*
[자료구조응용 15번 2번 정답 코드]

후위표현식(postfix expression)을 입력받아 산술식 이진트리를 생성한 후,
반복문을 사용하여

- iterInorder  : 중위순회 (iterative)
- iterPreorder : 전위순회 (iterative)
- levelOrder   : 레벨오더 순회 (circular queue 사용)

를 수행하는 프로그램.

- 입력 : input.txt 에 한 줄의 후위표현식 (예: AB/C*D*E+)
- 피연산자(operand) : 알파벳 한 글자
- 연산자(operator) : +, -, *, /, %

2024002779 김시연
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer root = NULL;

// stack (traversal에 사용)
treePointer stack[MAX_STACK_SIZE];
int top = -1;

// circular queue (level-order에 사용)
treePointer queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

char expr[81];

// ---------------- stack ----------------
void push(treePointer item) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack Full\n");
        exit(1);
    }
    stack[++top] = item;
}

treePointer pop(void) {
    if (top == -1)
        return NULL;    // empty 일 때 NULL
    return stack[top--];
}

int stackEmpty(void) {
    return top == -1;
}

// ---------------- queue ----------------
int queueEmpty(void) {
    return front == rear;
}

int queueFull(void) {
    return (rear + 1) % MAX_QUEUE_SIZE == front;
}

void addq(treePointer item) {
    if (queueFull()) {
        printf("Queue Full\n");
        exit(1);
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear] = item;
}

treePointer deleteq(void) {
    if (queueEmpty())
        return NULL;    // empty 일 때 NULL
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

// ---------------- tree 생성 ----------------
treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

treePointer createBinTree(void) {
    treePointer pNode;
    int i = 0;
    char symbol;

    top = -1;

    while ((symbol = expr[i]) != '\0') {
        if (symbol >= 'A' && symbol <= 'Z') {   // operand
            pNode = createNode(symbol);
            push(pNode);
        }
        else {                                  // operator
            pNode = createNode(symbol);
            pNode->rightChild = pop();
            pNode->leftChild  = pop();
            push(pNode);
        }
        i++;
    }
    return pop();
}

// ---------------- iterative traversals ----------------
void iterInorder(treePointer node) {
    top = -1;                 // 스택 초기화
    treePointer ptr = node;

    while (1) {
        // 왼쪽으로 끝까지 내려가면서 push
        while (ptr) {
            push(ptr);
            ptr = ptr->leftChild;
        }

        if (stackEmpty())     // 더 방문할 노드가 없으면 종료
            break;

        ptr = pop();          // 가장 위의 노드 방문
        printf("%c", ptr->data);
        ptr = ptr->rightChild;
    }
}

void iterPreorder(treePointer node) {
    top = -1;
    treePointer ptr = node;

    while (1) {
        // 왼쪽으로 내려가면서 방문 후 push
        while (ptr) {
            printf("%c", ptr->data); // 방문
            push(ptr);
            ptr = ptr->leftChild;
        }

        if (stackEmpty())
            break;

        ptr = pop();
        ptr = ptr->rightChild;
    }
}

// 레벨오더 순회
void levelOrder(treePointer ptr) {
    if (!ptr) return;

    front = rear = 0;     // 큐 초기화
    addq(ptr);

    while (!queueEmpty()) {
        treePointer cur = deleteq();
        printf("%c", cur->data);

        if (cur->leftChild)
            addq(cur->leftChild);
        if (cur->rightChild)
            addq(cur->rightChild);
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

    printf("Iter Inorder  : ");
    iterInorder(root);
    printf("\n");

    printf("Iter Preorder : ");
    iterPreorder(root);
    printf("\n");

    printf("Level Order   : ");
    levelOrder(root);
    printf("\n");

    return 0;
}
