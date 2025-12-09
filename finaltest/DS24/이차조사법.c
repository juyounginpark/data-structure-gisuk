/*
 * [변형 문제 1] Quadratic Probing
 *
 * [문제 설명]
 * 충돌 발생 시, (h(k) + i*i) % MAX 위치를 조사하는 이차 조사법을 구현하시오.
 * (i = 1, 2, ...)
 *
 * [입력 예시]
 * acos atoi char ... (input.txt)
 *
 * [출력 예시]
 * (해시 테이블 상태 출력)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 11
#define MAX_CHAR 10

typedef struct { char item[MAX_CHAR]; int key; } element;
element* ht[MAX];

unsigned int stringToInt(char *key) {
    int number = 0; while (*key) number += *key++; return number;
}
int h(int k) { return k % MAX; }

void insertQuadratic(char *str) {
    int key = stringToInt(str);
    int homeBucket = h(key);
    int i = 0;
    int currentBucket = homeBucket;

    while (ht[currentBucket] != NULL) {
        if (strcmp(ht[currentBucket]->item, str) == 0) return;
        i++;
        currentBucket = (homeBucket + i * i) % MAX; // Quadratic Probing
        if (i >= MAX) { printf("Table Full or infinite loop\n"); return; }
    }
    
    element *newElem = (element*)malloc(sizeof(element));
    strcpy(newElem->item, str); newElem->key = key;
    ht[currentBucket] = newElem;
}

int main() {
    char *data[] = {"acos", "atoi", "char", "define", "exp", "ceil", "cos", "float", "floor", "ctime"};
    for(int i=0; i<10; i++) insertQuadratic(data[i]);
    
    printf("Quadratic Probing Table:\n");
    for(int i=0; i<MAX; i++) {
        printf("[%d]: ", i);
        if(ht[i]) printf("%s (%d)", ht[i]->item, ht[i]->key);
        printf("\n");
    }
    return 0;
}