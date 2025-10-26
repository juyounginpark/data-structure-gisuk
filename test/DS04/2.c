#include <stdio.h>
#include <time.h>
#include "selectionSort.h"

#define MAX_SIZE 2001

void main()
{
    int i, n, step= 10;
    int a[MAX_SIZE];
    double duration;
    clock_t start;
    long repetitions;

    FILE *fp = fopen("out.txt", "w");
    if(fp == NULL) {
        printf("Error: Cannot open file out.txt\n");
        return;

    }
    
    puts("\tn repetitions\ttime\n");
    fprintf(fp,"\tn repetitions\ttime\n");

    for (n = 0; n <= 2000; n+= step)
    {
        repetitions = 0;

        start = clock();

        do {
            repetitions++;
            for(i = 0; i < n; i++)
                a[i] = n - i;
            sort(a, n);
        }while (clock() - start < 1000);

        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        duration /= repetitions;

        printf("%6d %9d %f\n", n, repetitions, duration);
        fprintf(fp, "%6d %9d %f\n", n, repetitions, duration);

        if(n == 100) step = 100;
    }

    fclose(fp);
    printf("\nAccurate performance measurement saved to out.txt\n");
    
}