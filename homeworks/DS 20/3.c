/*  
    2025002720 박주영
   본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    char name[20];
    int grade;
} element;

void insert(element e, element a[], int i) {
    a[0] = e;
    while (e.key < a[i].key) {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}

void insertionSort(element a[], int n) {
    int j;
    for (j = 2; j <= n; j++) {
        element temp = a[j];
        insert(temp, a, j - 1);
    }
}

int main() {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w+");
    
    if (fin == NULL || fout == NULL) {
        printf("파일 입출력 오류\n");
        return 1;
    }

    int n;
    fscanf(fin, "%d", &n);

    element *list = (element*)malloc(sizeof(element) * (n + 1));
    
    printf("<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    for (int i = 1; i <= n; i++) {
        fscanf(fin, "%d %s %d", &list[i].key, list[i].name, &list[i].grade);
        printf("<%d, %s, %d>\n", list[i].key, list[i].name, list[i].grade);
    }

    insertionSort(list, n);

    printf("\n<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>\n");
    for (int i = 1; i <= n; i++) {
        printf("<%d, %s, %d>\n", list[i].key, list[i].name, list[i].grade);
        fprintf(fout, "%d, %s, %d\n", list[i].key, list[i].name, list[i].grade);
    }

    free(list);
    fclose(fin);
    fclose(fout);

    return 0;
}