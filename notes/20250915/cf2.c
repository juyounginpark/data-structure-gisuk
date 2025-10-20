#include <stdio.h>
#define MAX_SIZE 100
float sum(float [], int);
void fill(float [], int);
float input[MAX_SIZE], answer;
void main(void)
{ 
	fill(input, MAX_SIZE);
	answer = sum(input, MAX_SIZE);
	printf("The sum is: %f\n", answer);
}

void fill(float list[], int n) 
{
	int i;
	for(i = 0; i < n; i++)
		list[i] = i;
}

float sum(float list[], int n)
{
	int i;
	float tempsum = 0;
	for(i = 0; i < n; i++)
		tempsum += list[i];
	return tempsum;
}
