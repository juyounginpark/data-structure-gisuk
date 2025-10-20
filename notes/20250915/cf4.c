#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) \
	if(!((p) = malloc(s))) {\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE);\
	}


int** make2dArray(int rows, int cols);

void main(void) {
   int** myArray;
   myArray = make2dArray(5, 10);
   myArray[2][4] = 6;
   printf("%d\n", myArray[2][4]);

}

int** make2dArray(int rows, int cols) {
   int** x, i;

   MALLOC(x, rows * sizeof(*x));
   for (i = 0; i < rows; ++i) {
      MALLOC(x[i], cols * sizeof(**x));
   }
   return x;
}