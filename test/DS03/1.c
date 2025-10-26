#include <stdio.h>

float sum(float list[], int n)
{
    float tempsum = 0;
    int i;
    for (i = 0; i < n; i++)
        tempsum += list[i];
    return tempsum;
}

float rsum(float list[], int n)
{
    if(n) return rsum(list, n-1) + list[n - 1];
    return 0;
}

int main(void)
{
    float list[10];
    int i;
    for (i = 0; i < 10; i++)
    {
        list[i] = (float)(i + 1);
    }

    printf("sum: 1에서 10까지의 합은 %f\n", sum(list , 10));
    printf("rsum: 1에서 10까지의 합은 %f\n", rsum(list, 10));

    return 0;
}