/*2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x, y) (((x) < (y)) ? -1: ((x) == (y)) ? 0: 1)
int a, b;
typedef struct 
{
    float coef;
    int exp;
}term;

term  terms[MAX_TERMS];
int avail = 0;

void attach(float coefficient, int exponent) 
{
    if(avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail++].exp = exponent;
}

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD)
{
    float coefficient;
    *startD = avail;
    while(startA <= finishA && startB <= finishB)
        switch (COMPARE(terms[startA].exp, terms[startB].exp))
        {
        case -1:
            attach(terms[startB].coef, terms[startB].exp);
            startB++;
            break;
        
        case 0:
            coefficient = terms[startA].coef + terms[startB].coef;
            if(coefficient)
                attach(coefficient, terms[startA].exp);
            startA++;
            startB++;
            break;
        case 1:
            attach(terms[startA].coef, terms[startA].exp);
            startA++;
            break;
        }

    for(; startA <= finishA; startA++)
        attach(terms[startA].coef, terms[startA].exp);
    for(; startB <= finishB; startB++)
        attach(terms[startB].coef, terms[startB].exp);
    *finishD = avail - 1;
}

void inputPoly(char *fname, int *startA, int *finishA, int *startB, int *finishB) 
{
    FILE *fp;
    fp = fopen(fname, "r");
    if(fp == NULL) {
        puts("파일 오픈 실패");
        return ;
    }
     fscanf(fp, "%d %d", &a, &b);
     for(int i = 0; i < a + b; i++) {
        fscanf(fp, "%f %d", &terms[i].coef, &terms[i].exp);
        avail++;
    }
    *startA = 0;
    *startB = a;
    *finishA = a - 1;
    *finishB = a + b - 1;
    
    

}
int main() {
    
    int startA, startB;
    int finishA, finishB;
    int startD, finishD;
    inputPoly("input.txt", &startA, &finishA, &startB, &finishB);

    puts("two input polynomials ...");  
    printf("A(x) = ");
    for(int i = 0; i < a; i++) {
        printf("%.1f", terms[i].coef);
        if(terms[i].exp == 0) break;
        printf("x^%d + ", terms[i].exp);
    }
    puts("");
    printf("B(x) = ");
    for(int i = a; i < a + b; i++) {
        printf("%.1f", terms[i].coef);
        if(terms[i].exp == 0) break;
        printf("x^%d + ", terms[i].exp);
    }
    puts("");
    puts("the result of polynomial addition ...");
    padd(startA, finishA, startB, finishB, &startD, &finishD);

    puts("D(x) = A(x) + B(x) =");
    for(int i = startD; i <= finishD; i++) {
        printf("%.1f", terms[i].coef);
        if(terms[i].exp == 0) break;
        printf("x^%d + ", terms[i].exp);
    }
    
}
