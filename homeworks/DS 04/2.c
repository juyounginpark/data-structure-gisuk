/*
 * 학번: [학번]
 * 이름: [이름]
 * 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <stdio.h>
#include <time.h>           // [cite: 137]
#include "selectionSort.h"  // [cite: 138]

// n을 2000까지 증가시키므로 MAX_SIZE를 2001로 수정 
#define MAX_SIZE 2001       // [cite: 139] (수정됨)

void main(void) { // [cite: 140]
    int i, n, step = 10;     // [cite: 142]
    int a[MAX_SIZE];         // [cite: 143]
    double duration;         // [cite: 144]
    long repetitions = 0;    // [cite: 149]
    clock_t start;           // [cite: 152]

    // 파일 열기 [cite: 39, 40]
    FILE *fp = fopen("out.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "파일 'out.txt'를 열 수 없습니다.\n");
        return;
    }

    // 화면 출력
    printf("      n   repetitions     time\n"); // [cite: 146, 151]
    // 파일 출력 
    fprintf(fp, "      n   repetitions     time\n");

    // n을 2000까지 증가 [cite: 37, 135]
    for (n = 0; n <= 2000; n += step) { // [cite: 147] (반복 조건 수정)
        
        repetitions = 0; // [cite: 149]
        start = clock(); // [cite: 154]

        do {
            repetitions++; // [cite: 155]
            
            /* initialize with worst-case data */ // [cite: 156]
            for (i = 0; i < n; i++) {
                a[i] = n - i; // [cite: 158]
            }
            sort(a, n); // [cite: 159]
        
        } while (clock() - start < 1000); // [cite: 160] (CLOCKS_PER_SEC가 1000이므로 약 1초)

        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; // [cite: 162, 164]
        duration /= repetitions; // [cite: 165] (반복 횟수로 나누어 평균 시간 계산)

        // 화면 출력 [cite: 166]
        printf("%6d   %9ld   %f\n", n, repetitions, duration);
        // 파일 출력 [cite: 38, 41]
        fprintf(fp, "%6d   %9ld   %f\n", n, repetitions, duration);

        if (n == 100) step = 100; // [cite: 167]
    }

    fclose(fp); // [cite: 42]
    printf("\n정교한 성능 측정 완료. 'out.txt' 파일이 생성되었습니다.\n");
}
