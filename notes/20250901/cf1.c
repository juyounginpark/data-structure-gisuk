#include <stdio.h>
#include <stdlib.h>
int main(){
    int i, *pi;
    float f, *pf;

    pi = (int *)malloc(sizeof(int)); // memory allocation in heap
    pf = (float *)malloc(sizeof(float)); // 힙 공간 안에서 주소를 반환함 with 형변환
    *pi = 1024;
    *pf = 3.14;
    printf("an integer = %d, a float = %f\n", *pi, *pf);
    free(pi);
    free(pf);
}
