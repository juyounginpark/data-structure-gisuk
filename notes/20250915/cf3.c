#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) \
	if(!((p) = malloc(s))) {\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FALLURE);\
	}

void main()
{
	float *pf;
	MALLOC(pf, sizeof(float));
}
