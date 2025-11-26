/*
    2025002720 박주영
    본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/
#include <stdio.h>
#include <stdlib.h>

int MAX_SIZE = 11;

typedef struct {
    int key;
} element;

void printState(element a[], int link[]) {
    int i;
    
    printf("      ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("[%2d] ", i);
    }
    printf("\n");

    printf("link: ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%4d ", link[i]);
    }
    printf("\n");

    printf("   a: ");
    printf("   - "); 
    for (i = 1; i < MAX_SIZE; i++) {
        printf("%4d ", a[i].key);
    }
    printf("\n\n");
}

int listMerge(element a[], int link[], int start1, int start2) {
    int last1 = start1;
    int last2 = start2;
    int lastResult = 0;

    while (last1 != 0 && last2 != 0) {
        if (a[last1].key <= a[last2].key) {
            link[lastResult] = last1;
            lastResult = last1;
            last1 = link[last1];
        } else {
            link[lastResult] = last2;
            lastResult = last2;
            last2 = link[last2];
        }
    }

    if (last1 == 0)
        link[lastResult] = last2;
    else
        link[lastResult] = last1;

    return link[0];
}

int rmergeSort(element a[], int link[], int left, int right) {
    printf("rmergeSort(a, link, %d, %d)\n", left, right);

    if (left >= right) return left;

    int mid = (left + right) / 2;

    int rightSorted = rmergeSort(a, link, mid + 1, right);
    int leftSorted = rmergeSort(a, link, left, mid);      
    
    int mergedResult = listMerge(a, link, leftSorted, rightSorted); 

    printf("\nlistMerged(a, link, %d, %d)\n", left, right);
    printState(a, link);

    return mergedResult;
}

int main() {
    element a[MAX_SIZE];
    int link[MAX_SIZE];
    int data[100];
    int count = 0;
    int n = 10;

    FILE *fp = fopen("input.txt", "r");
    if (fp != NULL) {
        while (count < n && fscanf(fp, "%d", &data[count]) == 1) {
            count++;
        }
        fclose(fp);
    } else {
        int defaultData[] = {26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
        for(int i=0; i<10; i++) data[i] = defaultData[i];
    }
    
    for (int i = 0; i < MAX_SIZE; i++) {
        link[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        a[i].key = data[i - 1];
    }

    printf("<<<<<<<<<< starting from initial 10 chains, >>>>>>>>>>\n");
    printf("<<<<<<<<<<<<<< each of which has one node >>>>>>>>>>>\n");
    printState(a, link);

    printf("<<<<<<<<<< executing recursive merge sort >>>>>>>>>>\n");

    int start = rmergeSort(a, link, 1, n);

    printf("<<<<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>>>>>>\n");
    int curr = start;
    while (curr != 0) {
        printf("%d ", a[curr].key);
        curr = link[curr];
    }
    printf("\n");

    return 0;
}