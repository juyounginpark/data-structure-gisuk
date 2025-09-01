/*
2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, *pi;
    float f, *pf;

    if ((pi = (int *) malloc(sizeof(int))) == NULL || (pf = (float *)malloc(sizeof(float)) == NULL))
    {
        fprintf(stderr, "Insufficient memory");
        exit(EXIT_FAILURE);
    }
    *pi = 1024;
    *pf = 3.14;
    printf("an integer = %d, a float = %f\n", *pi, *pf);
    free(pi);
    free(pf);
}