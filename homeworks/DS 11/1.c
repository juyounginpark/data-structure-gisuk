#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if(!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct listNode *listPointer;
typedef struct listNode {
    int data;
    listPointer link;
} listNode;

listPointer first = NULL;

void find(listPointer, listPointer*, int);
void insert(listPointer*, listPointer, int);
void delete(listPointer*, listPointer, listPointer);
void printList(listPointer);

int main(void) {
    int data;
    listPointer x;

    FILE *fp;
    if((fp = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "cannot open the file");
        exit(EXIT_FAILURE);
    }

    puts("The ordered list contains:");
    while(fscanf(fp, "%d", &data)!=EOF) {
        find(first, &x, data);
        insert(&first, x, data);
    }
    printList(first);

    puts("After deleting nodes with data less than and equal to 50");

    listPointer temp = first;
    listPointer trail = NULL;

    while (temp) {
        if (temp->data <= 50) {
            delete(&first, trail, temp);
            if (trail == NULL)
                temp = first;
            else
                temp = trail->link;
        } else {
            trail = temp;
            temp = temp->link;
        }
    }

    printList(first);
}

void find(listPointer first, listPointer *x, int data) {
    listPointer pre = NULL;
    listPointer trav = first;

    if(first == NULL) {
        *x = NULL;
    } else {
        if(trav->data > data) {
            *x = NULL;
            return;
        }
        while(trav) {
            pre = trav;
            trav = trav->link;
            if(trav && trav->data > data) break;
        }
        *x = pre;
    }
}

void insert(listPointer* first, listPointer x, int data) {
    listPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->data = data;

    if(*first == NULL) {
        temp->link = NULL;
        *first = temp;
    } else {
        if(x == NULL) {
            temp->link = *first;
            *first = temp;
        } else {
            temp->link = x->link;
            x->link = temp;
        }
    }
}

void delete(listPointer* first, listPointer trail, listPointer x) {
    if(trail)
        trail->link = x->link;
    else
        *first = (*first)->link;
    free(x);
}

void printList(listPointer first) {
    printf("The list contains: \n");
    for(int i = 1; first; first = first->link, i++) {
        printf("%4d", first->data);
        if(!(i%10)) putchar('\n');
    }
    printf("\n");
}
