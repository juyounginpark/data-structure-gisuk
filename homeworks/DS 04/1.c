/*
 * 학번: [학번]
 * 이름: [이름]
 * 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <stdio.h>
#include <time.h>           // [cite: 5]
#include "selectionSort.h"  // [cite: 6]

// n을 2000까지 증가시키므로 MAX_SIZE를 2001로 수정 
#define MAX_SIZE 2001       // [cite: 7] (수정됨)

void main(void) { // [cite: 8]
    int i, n, step = 10; // [cite: 9]
    int a[MAX_SIZE];     // [cite: 10]
    double duration;     // [cite: 11]
    clock_t start;       // [cite: 12]

    // 파일 열기 [cite: 39, 40]
    FILE *fp = fopen("out.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "파일 'out.txt'를 열 수 없습니다.\n");
        return;
    }

    // 화면 출력
    printf("      n     time\n"); // [cite: 13, 14]
    // 파일 출력 
    fprintf(fp, "      n     time\n");

    // n을 2000까지 증가 
    for (n = 0; n <= 2000; n += step) { // [cite: 14, 17] (반복 조건 수정)

        /* initialize with worst-case data */ // [cite: 18]
        for (i = 0; i < n; i++) {
            a[i] = n - i; // [cite: 20]
        }
        
        start = clock(); // [cite: 21]
        sort(a, n);      // [cite: 21]
        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; // [cite: 22, 25]

        // 화면 출력 [cite: 24]
        printf("%6d   %f\n", n, duration);
        // 파일 출력 [cite: 38, 41]
        fprintf(fp, "%6d   %f\n", n, duration);

        if (n == 100) step = 100; // [cite: 24]
    }

    fclose(fp); // [cite: 42]
    printf("\n성능 측정 완료. 'out.txt' 파일이 생성되었습니다.\n");
}
