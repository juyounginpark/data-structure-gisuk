 /*
2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if(!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }

#define COMPARE(a, b) (a > b? 1 : (a==b ? 0 : -1))
typedef struct polyNode *polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
}polyNode;

polyPointer a = NULL, b = NULL, c = NULL;

void insert(polyPointer* first, polyPointer x, int co, int ex) {
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->coef = co;
    temp->expon = ex;

    if(*first == NULL) 
    {
        temp->link = NULL;
        *first = temp;
    }
    else
    {
        if(x == NULL) {
           temp->link = *first;
           *first = temp;
        }
        else {
            temp->link = x->link;
            x->link = temp;
        }
    }
}

void find(polyPointer first, polyPointer *x) {
    polyPointer pre = NULL;
    polyPointer trav = first;

    if(first == NULL)
    {
        //empty list
        *x = NULL;
    }
    else
    {
        //non-empty list
        while(trav) {
            pre = trav;
            trav = trav->link;

        }

        *x = pre;
    }
}

void printList(polyPointer first) {
    for(; first; first = first->link)  {
        printf("%+4d", first->coef);
        if(first->expon)printf("x^%d ",first->expon);
    }

        
    puts("");
}

void attach(float coefficient, int exponent, polyPointer *ptr)
{
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

void erase(polyPointer *ptr)
{
    polyPointer temp;
    while(*ptr) {
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}


polyPointer padd(polyPointer a, polyPointer b)
{
    polyPointer c, rear, temp;
    int sum;
    MALLOC(rear, sizeof(*rear));
    c = rear;
    while (a&&b)
        switch (COMPARE(a->expon, b->expon))
        {
        case -1:
            attach(b->coef, b->expon, &rear);
            b = b->link;
            break;
        
        case 0:
            sum = a->coef + b->coef;
            if(sum) attach(sum, a->expon, &rear);
            a = a->link; b = b->link; break;

        case 1:
            attach(a->coef, a->expon, &rear);
            a = a->link;
            break;
        }
    for(; a; a = a->link) attach(a->coef, a->expon, &rear);
    for(; b; b = b->link) attach(b->coef, b->expon, &rear);
    rear->link = NULL;
    temp = c; c = c->link; free(temp);
    return c;
}

void inputPoly(char *filename, polyPointer *p) {
    FILE *fp = fopen(filename, "r");
    char type;
    fscanf(fp, "%c", &type);
    polyPointer x;

    int co, ex;

    if(type == 'a') {
        while(fscanf(fp, "%d %d", &co, &ex) != EOF) {
            insert(p, x, co, ex);
        }
    }
    else {
        while(fscanf(fp, "%d %d", &co, &ex) != EOF) {
            find(*p, &x);
            insert(p, x, co, ex);
        }
    }
    fclose(fp);

    return;
}

int main() {
    inputPoly("a.txt", &a);
    inputPoly("b.txt", &b);
    printf("a: ");
    printList(a);
    printf("b: ");
    printList(b);
    printf("a+b=c: ");
    c = padd(a, b);
    printList(c);
    erase(&a);
    erase(&b);
    erase(&c);



}
