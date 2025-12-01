
/*
2025002720 박주영
본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접          작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 200

typedef struct {
    int key;
} element;

void adjust(element a[], int root, int n);
void heapSort(element a[], int n);
void printList(element a[], int n);

FILE *fp_out;

int main() {
    FILE *fp_in = fopen("input.txt", "r");
    fp_out = fopen("output.txt", "w");

    if (fp_in == NULL) {
        printf("input.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    int n;
    if (fscanf(fp_in, "%d", &n) == EOF) {
        return 1;
    }

    element *a = (element *)malloc(sizeof(element) * (n + 1));

    printf("<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    fprintf(fp_out, "<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");

    for (int i = 1; i <= n; i++) {
        fscanf(fp_in, "%d", &a[i].key);
        printf("%d ", a[i].key);
        fprintf(fp_out, "%d ", a[i].key);
    }
    printf("\n\n");
    fprintf(fp_out, "\n\n");

    heapSort(a, n);

    printf("<<<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>\n");
    fprintf(fp_out, "<<<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>\n");
    printList(a, n);

    fclose(fp_in);
    fclose(fp_out);
    free(a);
    return 0;
}

void adjust(element a[], int root, int n) {
    int child, rootkey;
    element temp;

    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root;

    while (child <= n) {
        if ((child < n) && (a[child].key < a[child+1].key))
            child++;

        if (rootkey > a[child].key)
            break;
        else {
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

void heapSort(element a[], int n) {
    int i;
    element temp;

    printf("<<<<<<<< executing heap sort >>>>>>>>>>\n");
    fprintf(fp_out, "<<<<<<<< executing heap sort >>>>>>>>>>\n");

    for (i = n / 2; i > 0; i--)
        adjust(a, i, n);

    printf("after initialization of max heap...\n");
    fprintf(fp_out, "after initialization of max heap...\n");
    printList(a, n);
    printf("\n"); fprintf(fp_out, "\n");

    int step = 1;
    for (i = n - 1; i > 0; i--) {
        // SWAP
        temp = a[1];
        a[1] = a[i + 1];
        a[i + 1] = temp;

        adjust(a, 1, i);

        printf("step %2d: ", step);
        fprintf(fp_out, "step %2d: ", step);

        for (int k = 1; k <= n; k++) {
            printf("%d ", a[k].key);
            fprintf(fp_out, "%d ", a[k].key);
        }
        printf("\n");
        fprintf(fp_out, "\n");
        step++;
    }
    printf("\n"); fprintf(fp_out, "\n");
}

void printList(element a[], int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i].key);
        fprintf(fp_out, "%d ", a[i].key);
    }
    printf("\n");
    fprintf(fp_out, "\n");
}
