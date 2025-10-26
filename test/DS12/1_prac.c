#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if(!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }

#define COMPARE(a, b) (a > b ? 1 : (a == b ? 0 : -1))

typedef struct polyNode *polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
} polyNode;

polyPointer a = NULL, b = NULL, c = NULL;

void inputPoly(char*, polyPointer *);
void insert(polyPointer*, polyPointer, int, int);
void printPoly(char *, polyPointer);
void find(polyPointer, polyPointer *)

int main() {

}

void inputPoly(char* filename, polyPointer *p) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char type;
    fscanf(fp, "%c", &type);

    polyPointer x = NULL;
    int co, ex;

    if (type == 'a') {
        while(fscanf(fp, "%d %d", &co, &ex) != EOF) {
            insert(p, NULL, co, ex);
        }
    }
    else {
        while(fscanf(fp, "%d %d", &co, &ex) != EOF) {
            find(*p, &x);
            insert(p, x, co, ex);
        }
    }
    fclose(fp);
}

void find(polyPointer first, polyPointer *x) {
    polyPointer pre = NULL;
    polyPointer trav = first;

    if (first == NULL) {
        *x = NULL;

    }
    else {
        while(trav) {
            prv = trav;
            trav = trav -> link;
        }
        *x = pre;
    }
}

void insert(polyPointer* first, polyPointer x, int co, int ex) {
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));

    temp->coef = co;
    temp->expon = ex;

    if(*first == NULL) {
        temp -> link = NULL;
        *first = temp;
    }
    else if(x == NULL) {
        temp -> link = *first;
        *first = temp;
    }
    else {
        temp->link = x->link;
        x->link = temp;
    }
}

void printPoly(char *name, polyPointer first) {
    printf("%-8s: ", name);
    if(!first) {
        printf("0\n");
        return;
    }

    polyPointer ptr = first;

    if(ptr->coef > 0) putchar("+");
    printf("%d", ptr->coef);

    if(ptr->expon > 1) printf("x^%d", ptr->expon);
    else if(ptr->expon == 1) putchar('x');

    for(ptr = ptr->link; ptr; ptr = ptr->link) {
        if(ptr->coef > 0) printf(" +");
        else printf(" ");
        printf("%d", ptr->coef);

        if(ptr->expon > 1) printf("x^%d", ptr->expon);
        else if (ptr->expon == 1) putchar('x');

    }
    puts("");
}  