/*
 * [문제 2] Iterative Merge Sort
 *
 * [문제 설명]
 * 입력 파일(input.txt)로부터 데이터를 읽어 반복적 합병 정렬(Iterative Merge Sort)을 수행하시오.
 * 각 mergePass 수행 후 세그먼트 크기(s)와 배열 a, extra의 상태를 출력하시오.
 *
 * [입력 예시 (input.txt)]
 * 11
 * 12 2 16 30 8 28 4 10 20 6 18
 *
 * [출력 예시]
 * segment size: 1
 * a:     12   2  16 ...
 * extra:  2  12  16 ...
 * segment size: 2
 * extra:  2  12  16 ...
 * a:      2  12  16 ...
 * ...
 * >>> Sorted List <<<
 * 2 4 6 8 10 12 16 18 20 28 30
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int key;
} element;

element list[MAX_SIZE];
int n;

void printArray(const char* name, element a[], int size) {
    printf("%6s: ", name);
    for (int i = 1; i <= size; i++) {
        printf("%4d", a[i].key);
    }
    printf("\n");
}

// Program 7.7: Merging two sorted lists
void merge(element initList[], element mergedList[], int i, int m, int n) {
    int j, k, t;
    j = m + 1; // 두 번째 부분 리스트의 시작 인덱스
    k = i;     // 합병 리스트의 인덱스

    while (i <= m && j <= n) {
        if (initList[i].key <= initList[j].key)
            mergedList[k++] = initList[i++];
        else
            mergedList[k++] = initList[j++];
    }

    if (i > m) {
        for (t = j; t <= n; t++)
            mergedList[k + t - j] = initList[t];
    }
    else {
        for (t = i; t <= m; t++)
            mergedList[k + t - i] = initList[t];
    }
}

// Program 7.8: A merge pass
void mergePass(element initList[], element mergedList[], int n, int s) {
    int i, j;
    for (i = 1; i <= n - 2 * s + 1; i += 2 * s) {
        merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
    }
    
    // 남은 길이가 2*s 보다 작지만 s보다는 클 때 (하나의 온전한 세그먼트 + 자투리)
    if (i + s - 1 < n) {
        merge(initList, mergedList, i, i + s - 1, n);
    }
    else { // 남은 길이가 s보다 작거나 같을 때 (그냥 복사)
        for (j = i; j <= n; j++) {
            mergedList[j] = initList[j];
        }
    }
}

// Program 7.9: Merge sort (Modified for Output)
void mergeSort(element a[], int n) {
    int s = 1; // current segment size
    element extra[MAX_SIZE];

    printf("<<<<<<<< executing Iterative merge sort >>>>>>>>\n");

    while (s < n) {
        printf("segment size: %d\n", s);
        
        // Pass 1: a -> extra
        printArray("a", a, n);
        mergePass(a, extra, n, s);
        printArray("extra", extra, n);
        s *= 2;

        // Pass 2: extra -> a (if needed)
        if (s < n) { // 다음 단계가 있을 때만 출력 및 실행
             printf("segment size: %d\n", s);
             printArray("extra", extra, n);
             mergePass(extra, a, n, s);
             printArray("a", a, n);
             s *= 2;
        } else { // s >= n 이면 정렬 완료. 마지막 결과가 extra에 있음 -> a로 복사
             for(int k=1; k<=n; k++) a[k] = extra[k];
        }
    }
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (!fp) return 1;

    fscanf(fp, "%d", &n);
    for (int i = 1; i <= n; i++) {
        fscanf(fp, "%d", &list[i].key);
    }
    fclose(fp);

    printf("<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    for(int i=1; i<=n; i++) printf("%4d", list[i].key);
    printf("\n");

    mergeSort(list, n);

    printf("<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>>>>\n");
    for (int i = 1; i <= n; i++) {
        printf("%4d ", list[i].key);
    }
    printf("\n");

    return 0;
}