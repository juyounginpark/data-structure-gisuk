#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
	if(!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

int main(){
	int *pi;	
	MALLOC(pi, sizeof(int));
	*pi = 1;
	printf("%d\n", *pi);
}
