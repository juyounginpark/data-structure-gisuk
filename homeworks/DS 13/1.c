/*
2025002720
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MALLOC(p, s) if(!((p) = malloc(s))) {fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}
#define COMPARE(a, b) (a > b ? 1 : (a == b ? 0 : -1))

typedef struct polyNode *polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
} polyNode;

polyPointer a = NULL, b = NULL, c = NULL;
polyPointer lastA, lastB, lastC;
polyPointer avail = NULL;

polyPointer getNode() {
    polyPointer node;
    if (avail) {
        node = avail;
        avail = avail->link;
    } else MALLOC(node, sizeof(*node));
    return node;
}

void retNode(polyPointer node) {
    node->link = avail;
    avail = node;
}

void insertFrontCL(polyPointer *last, polyPointer node) {
    polyPointer header = (*last)->link;
    if (header == *last) {
        node->link = header;
        header->link = node;
        *last = node;
    } else {
        node->link = header->link;
        header->link = node;
    }
}

void insertLastCL(polyPointer *last, polyPointer node) {
    polyPointer header = (*last)->link;
    node->link = header;
    (*last)->link = node;
    *last = node;
}

void printCList(polyPointer header, polyPointer *last) {
    if (!header) return;
    polyPointer temp = header->link;
    while (temp != header) {
        printf("%+4d", temp->coef);
        if (temp->expon) printf("x^%d ", temp->expon);
        temp = temp->link;
    }
    puts("");
}

void attach(int coefficient, int exponent, polyPointer *ptr) {
    polyPointer temp = getNode();
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

void erase(polyPointer *ptr) {
    polyPointer temp;
    while (*ptr) {
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
} 

void cerase(polyPointer *ptr) {
    if (!*ptr) return;
    polyPointer header = *ptr;
    polyPointer temp = header->link;
    
    if (temp == header) {
        retNode(header);
        *ptr = NULL;
        return;
    }
    
    polyPointer last = header;
    while (last->link != header) {
        last = last->link;
    }
    
    last->link = avail;
    avail = header;
    *ptr = NULL;
}

polyPointer cpadd(polyPointer a, polyPointer b) {
    polyPointer startA, c, lastC;
    int sum, done = FALSE;
    startA = a;
    a = a->link;
    b = b->link;
    c = getNode();
    c->expon = -1;
    lastC = c;
    do {
        switch (COMPARE(a->expon, b->expon)) {
            case -1:
                attach(b->coef, b->expon, &lastC);
                b = b->link;
                break;
            case 0:
                if (startA == a) done = TRUE;
                else {
                    sum = a->coef + b->coef;
                    if (sum) attach(sum, a->expon, &lastC);
                    a = a->link;
                    b = b->link;
                }
                break;
            case 1:
                attach(a->coef, a->expon, &lastC);
                a = a->link;
        }
    } while (!done);
    lastC->link = c;
    return c;
}

void inputPolyCL(char *filename, polyPointer *header, polyPointer *last) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    char order;
    int coef, expon;
    polyPointer node;

    fscanf(fp, " %c", &order);

    *header = getNode();
    (*header)->coef = 0;
    (*header)->expon = -1;
    (*header)->link = *header;
    *last = *header;

    while (fscanf(fp, "%d %d", &coef, &expon) == 2) {
        node = getNode();
        node->coef = coef;
        node->expon = expon;
        if (order == 'd') insertLastCL(last, node);
        else insertFrontCL(last, node);
    }
    fclose(fp);
}

int main() {
    inputPolyCL("a.txt", &a, &lastA);
    inputPolyCL("b.txt", &b, &lastB);
    
    printf("a: ");
    printCList(a, &lastA);
    
    printf("b: ");
    printCList(b, &lastB);
    
    printf("a+b=c: ");
    c = cpadd(a, b);
    printCList(c, &lastC);
    
    cerase(&a);
    cerase(&b);
    cerase(&c);
    
    erase(&avail);
    
    return 0;
}