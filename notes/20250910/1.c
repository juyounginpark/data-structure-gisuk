#include <stdio.h>
#include <time.h>
#include "selectionSort.h"

#define MAX_SIZE 2001

int main(void) {
    FILE *fp = fopen("out.txt", "w+");


	int i, n, step = 10;
    int a[MAX_SIZE];
    double duration;
	
    fprintf(fp,"\tn\trepetitions\ttime\n");
    for (n = 0; n <= 2000; n += step) {
        long repetitions = 0;
        clock_t start = clock();
        do {
            repetitions++;

            for (i = 0; i < n; i++)
                a[i] = n - i;

            sort(a, n);
        } while (clock() - start < 1000);

        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        duration /= repetitions;

        fprintf(fp,"%6d\t%9ld\t%f\n", n, repetitions, duration);
        if (n == 100) step = 100;
    }
	fclose(fp);
    return 0;
}
