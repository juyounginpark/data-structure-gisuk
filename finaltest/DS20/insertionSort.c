/*
 * [문제 3] Insertion Sort with Struct
 *
 * [문제 설명]
 * 파일로부터 (key, name, grade) 데이터를 읽어 key를 기준으로 삽입 정렬을 수행하고
 * 결과를 화면 출력 및 output.txt에 저장하시오.
 *
 * [입력 예시 (input.txt)]
 * 7
 * 10 송중기 95
 * 35 조인성 89
 * ...
 *
 * [출력 예시]
 * <<<<<<<<<<<<<< Input List >>>>>>>>>>>>>
 * < 10, 송중기, 95 >
 * ...
 * <<<<<<<<<<<<<< Sorted List >>>>>>>>>>
 * < 10, 송중기, 95 >
 * < 11, 박용우, 78 >
 * ...
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    char name[20];
    int grade;
} element;

// Program 7.4 응용 [cite: 131-137]
void insert(element e, element a[], int i) {
    a[0] = e; // sentinel
    while (e.key < a[i].key) {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}

// Program 7.5 응용 [cite: 139-146]
void insertionSort(element a[], int n) {
    int j;
    for (j = 2; j <= n; j++) {
        element temp = a[j];
        insert(temp, a, j - 1);
    }
}

int main() {
    FILE* fp_in = fopen("input.txt", "r");
    FILE* fp_out = fopen("output.txt", "w");
    if (!fp_in || !fp_out) return 1;

    int n;
    fscanf(fp_in, "%d", &n);

    // 1-based indexing을 위해 크기 n+1 할당
    element* list = (element*)malloc(sizeof(element) * (n + 1));

    printf("<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    for (int i = 1; i <= n; i++) {
        fscanf(fp_in, "%d %s %d", &list[i].key, list[i].name, &list[i].grade);
        printf("< %d, %s, %d >\n", list[i].key, list[i].name, list[i].grade);
    }

    insertionSort(list, n);

    printf("\n<<<<<<<<<<<<<< Sorted List >>>>>>>>>>\n");
    for (int i = 1; i <= n; i++) {
        printf("< %d, %s, %d >\n", list[i].key, list[i].name, list[i].grade);
        fprintf(fp_out, "< %d, %s, %d >\n", list[i].key, list[i].name, list[i].grade);
    }

    fclose(fp_in);
    fclose(fp_out);
    free(list);
    return 0;
}