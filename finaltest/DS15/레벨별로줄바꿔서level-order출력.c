/*
[변형 문제 5]
후위표현식으로부터 산술식 이진트리를 생성한 뒤,
레벨오더(level-order) 순회를 하되 각 레벨을 줄바꿈하여 출력하는 프로그램을 작성하라.

예)
어떤 트리에 대해 레벨오더 방문 순서가 A B C D E F G 라면,

출력 형식
Level 1 : A
Level 2 : B C
Level 3 : D E F G

를 출력한다. (레벨 번호는 루트를 1로 한다.)

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

typedef struct {
    treePointer ptr;
    int level;
} QItem;

treePointer stack[MAX_STACK_SIZE];
int top = -1;
char expr[81];

QItem queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

// ----- stack -----
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

// ----- queue -----
int queueEmpty(void) {
    return front == rear;
}

int queueFull(void) {
    return (rear + 1) % MAX_QUEUE_SIZE == front;
}

void addq(treePointer ptr, int level) {
    if (queueFull()) {
        printf("Queue Full\n");
        exit(1);
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear].ptr = ptr;
    queue[rear].level = level;
}

QItem deleteq(void) {
    QItem item;
    if (queueEmpty()) {
        item.ptr = NULL;
        item.level = 0;
        return item;
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
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

void levelOrderByLevel(treePointer root) {
    if (!root) return;

    front = rear = 0;
    addq(root, 1);

    int currentLevel = 0;

    while (!queueEmpty()) {
        QItem item = deleteq();
        treePointer node = item.ptr;
        int level = item.level;

        if (!node) continue;

        if (level != currentLevel) {
            if (currentLevel != 0) printf("\n");
            printf("Level %d : ", level);
            currentLevel = level;
        }

        printf("%c ", node->data);

        if (node->leftChild)
            addq(node->leftChild, level + 1);
        if (node->rightChild)
            addq(node->rightChild, level + 1);
    }
    printf("\n");
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

    levelOrderByLevel(root);

    return 0;
}
