#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild, centerChild;
} node;

// 노드 하나 생성
treePointer createNode(char data) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    if (!newNode) {
        printf("malloc error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = newNode->centerChild = NULL;
    return newNode;
}

/*
 width : 한 줄에 들어갈 문자 개수 (항상 홀수, 최소 3)
 isLastLevel : 마지막 레벨이면 가운데를 'H'로 찍고, 아니면 '|'
 
 반환값 : 이 줄의 가운데 노드 포인터 (centerChild 체인에 사용)
*/
treePointer makeRow(int width, int isLastLevel) {
    treePointer *arr = (treePointer *)malloc(sizeof(treePointer) * width);
    if (!arr) {
        printf("malloc error\n");
        exit(1);
    }

    int mid = width / 2;

    for (int i = 0; i < width; i++) {
        char ch;
        if (i == 0)              ch = '/';        // 맨 왼쪽
        else if (i == width - 1) ch = '\\';       // 맨 오른쪽
        else if (i == mid && isLastLevel)
            ch = 'H';                              // 마지막 레벨의 가운데
        else
            ch = '|';                              // 나머지 가지

        arr[i] = createNode(ch);
    }

    // 왼쪽/오른쪽 이웃끼리 연결
    for (int i = 0; i < width; i++) {
        if (i > 0)         arr[i]->leftChild  = arr[i - 1];
        if (i < width - 1) arr[i]->rightChild = arr[i + 1];
    }

    treePointer center = arr[mid];
    free(arr); // 노드 자체는 heap에 남아 있고, 배열만 해제
    return center;
}

treePointer makeRow2(int width, int isLastLevel) {
    treePointer *arr = (treePointer *)malloc(sizeof(treePointer) * width);
    if (!arr) {
        printf("malloc error\n");
        exit(1);
    }

    int mid = width / 2;

    for (int i = 0; i < width; i++) {
        char ch;
        if (i == 0)              ch = '/';        // 맨 왼쪽
        else if (i == width - 1) ch = '\\';       // 맨 오른쪽
        else if (i == mid && isLastLevel)
            ch = 'H';                              // 마지막 레벨의 가운데
        else
            ch = ':';                              // 나머지 가지

        arr[i] = createNode(ch);
    }

    // 왼쪽/오른쪽 이웃끼리 연결
    for (int i = 0; i < width; i++) {
        if (i > 0)         arr[i]->leftChild  = arr[i - 1];
        if (i < width - 1) arr[i]->rightChild = arr[i + 1];
    }

    treePointer center = arr[mid];
    free(arr); // 노드 자체는 heap에 남아 있고, 배열만 해제
    return center;
}
/*
 levels : 별(*) 아래로 내려갈 삼각형 레벨 수
 반환값 : 맨 위 별 노드 포인터
*/
treePointer buildChristmasTree(int levels) {
    // 맨 위 별
    treePointer star = createNode('*');

    treePointer curCenter = star;
    int width = 3;  // 첫 레벨의 너비

    // 가지 레벨 만들기
    for (int lv = 0; lv < levels; lv++) {
        int isLast = (lv == levels - 1);  // 마지막 레벨 여부
        
        treePointer rowCenter;
        if(lv%2)
            rowCenter = makeRow(width, isLast);
        else 
            rowCenter = makeRow2(width, isLast);

        curCenter->centerChild = rowCenter;  // 위 레벨의 가운데와 연결
        curCenter = rowCenter;
        width += 2; // 아래로 갈수록 가지 폭 증가 (3,5,7,...)
    }

    // 기둥 두 칸 추가
    treePointer trunk1 = createNode('|');
    treePointer trunk2 = createNode('|');
    curCenter->centerChild = trunk1;
    trunk1->centerChild = trunk2;

    return star;
}

// 한 줄(레벨)의 가운데 노드를 알고 있을 때, 왼쪽 끝까지 간 후 오른쪽으로 쭉 출력
void printRow(treePointer center, int width) {
    treePointer p = center;
    while (p->leftChild) {
        p = p->leftChild;
    }
    for (int i = 0; i < width; i++) {
        putchar(p->data);
        p = p->rightChild;
    }
}

/*
 트리를 예쁘게 출력
 levels : 삼각형 레벨 수 (buildChristmasTree 에서 사용한 값과 동일해야 함)
*/
void printChristmasTree(treePointer star, int levels) {
    // 제일 아래 가지의 최대 폭
    int maxWidth = 3 + 2 * (levels - 1);

    // 1. 맨 위 별 출력
    int indentStar = (maxWidth - 1) / 2;
    for (int i = 0; i < indentStar; i++) putchar(' ');
    putchar(star->data);
    putchar('\n');

    // 2. 가지 레벨 출력
    int width = 3;
    treePointer center = star->centerChild;
    for (int lv = 0; lv < levels; lv++) {
        int indent = (maxWidth - width) / 2;
        for (int i = 0; i < indent; i++) putchar(' ');
        printRow(center, width);
        
        putchar('\n');

        center = center->centerChild; // 다음 레벨로 내려감
        width += 2;
    }

    int trunkIndent = (maxWidth - 1) / 2;
    for (int t = 0; t < 2 && center; t++) {
        for (int i = 0; i < trunkIndent; i++) putchar(' ');
        putchar(center->data);
        putchar('\n');
        center = center->centerChild;
    }
}

int main(void) {
    int levels = 12;  
    treePointer star = buildChristmasTree(levels);
    printChristmasTree(star, levels);
    return 0;
}
