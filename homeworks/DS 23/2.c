/*
 	2025002720 박주영
  	본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int key;
} element;

FILE *fp_out;

int digit(element e, int j, int r) {
    int divisor = 1;
    for (int k = 0; k < j; k++) divisor *= r;
    return (e.key / divisor) % r;
}

void printState(const char* title, element a[], int link[], int first, int n, int *front, int *rear, int r, int printQueues) {
    printf("************************* %s *********************\n", title);
    fprintf(fp_out, "************************* %s *********************\n", title);

    for (int i = 1; i <= n; i++) {
        printf("[%2d] ", i);
        fprintf(fp_out, "[%2d] ", i);
    }
    printf("\n"); fprintf(fp_out, "\n");

    printf("link: "); fprintf(fp_out, "link: ");
    for (int i = 1; i <= n; i++) {
        printf("%4d ", link[i]);
        fprintf(fp_out, "%4d ", link[i]);
    }
    printf("\n"); fprintf(fp_out, "\n");

    printf("   a: "); fprintf(fp_out, "   a: ");
    for (int i = 1; i <= n; i++) {
        printf("%4d ", a[i].key);
        fprintf(fp_out, "%4d ", a[i].key);
    }
    printf("\n"); fprintf(fp_out, "\n");

    printf("first: %4d\n\n", first);
    fprintf(fp_out, "first: %4d\n\n", first);

    printf("result: "); fprintf(fp_out, "result: ");
    int current = first;
    while (current != 0) {
        printf("%d ", a[current].key);
        fprintf(fp_out, "%d ", a[current].key);
        current = link[current];
    }
    printf("\n\n"); fprintf(fp_out, "\n\n");

    if (printQueues && front != NULL && rear != NULL) {
        for (int i = 0; i < r; i++) {
            printf("[%2d] ", i);
            fprintf(fp_out, "[%2d] ", i);
        }
        printf("\n"); fprintf(fp_out, "\n");

        printf("rear: "); fprintf(fp_out, "rear: ");
        for (int i = 0; i < r; i++) {
            printf("%4d ", rear[i]);
            fprintf(fp_out, "%4d ", rear[i]);
        }
        printf("\n"); fprintf(fp_out, "\n");

        printf("front:"); fprintf(fp_out, "front:");
        for (int i = 0; i < r; i++) {
            printf("%4d ", front[i]);
            fprintf(fp_out, "%4d ", front[i]);
        }
        printf("\n\n"); fprintf(fp_out, "\n\n");
    }
}

int radixSort(element a[], int link[], int d, int r, int n) {
    int *front = (int *)malloc(sizeof(int) * r);
    int *rear = (int *)malloc(sizeof(int) * r);
    
    int i, bin, current, first, last;

    first = 1;
    for (i = 1; i < n; i++) link[i] = i + 1;
    link[n] = 0;

    printState("initial chain", a, link, first, n, NULL, NULL, r, 0);

    for (i = 0; i < d; i++) {
        for (bin = 0; bin < r; bin++) {
            front[bin] = 0;
            rear[bin] = 0; 
        }

        for (current = first; current != 0; current = link[current]) {
            bin = digit(a[current], i, r);
            if (front[bin] == 0)
                front[bin] = current;
            else
                link[rear[bin]] = current;
            rear[bin] = current;
        }

        for (bin = 0; bin < r && front[bin] == 0; bin++); // 첫 번째 비어있지 않은 빈 찾기
        
        if (bin < r) {
            first = front[bin];
            last = rear[bin];
            
            for (bin++; bin < r; bin++) {
                if (front[bin] != 0) {
                    link[last] = front[bin];
                    last = rear[bin];
                }
            }
            link[last] = 0;
        }

        char passTitle[20];
        sprintf(passTitle, "pass %d", i + 1);
        printState(passTitle, a, link, first, n, front, rear, r, 1);
    }

    free(front);
    free(rear);
    return first;
}

int main() {
    FILE *fp_in = fopen("input.txt", "r");
    fp_out = fopen("output.txt", "w");

    if (fp_in == NULL) {
        printf("input.txt를 찾을 수 없습니다.\n");
        return 1;
    }

    int d, n; 
    fscanf(fp_in, "%d %d", &d, &n);

    element *a = (element *)malloc(sizeof(element) * (n + 1));
    int *link = (int *)malloc(sizeof(int) * (n + 1));
    int r = 10; 

    for (int i = 1; i <= n; i++) {
        fscanf(fp_in, "%d", &a[i].key);
    }

    radixSort(a, link, d, r, n);


    fclose(fp_in);
    fclose(fp_out);
    free(a);
    free(link);

    return 0;
}
