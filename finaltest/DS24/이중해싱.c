/*
 * [변형 문제 3] Double Hashing
 *
 * [문제 설명]
 * 이중 해싱을 사용하여 충돌을 해결하시오.
 * h1(k) = k % 11
 * h2(k) = 7 - (k % 7)  (Step size, 0이 되면 안됨)
 *
 * [입력 예시]
 * (동일 데이터)
 *
 * [출력 예시]
 * (해시 테이블 상태)
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
int h1(int k) { return k % MAX; }
int h2(int k) { return 7 - (k % 7); } // 두 번째 해시 함수

void insertDouble(char *str) {
    int key = stringToInt(str);
    int bucket = h1(key);
    int step = h2(key);
    int i = 0;

    while (ht[bucket] != NULL) {
        bucket = (bucket + step) % MAX; // Double Hashing
        i++;
        if (i >= MAX) return; // Table Full check logic needed
    }
    
    ht[bucket] = (element*)malloc(sizeof(element));
    strcpy(ht[bucket]->item, str); ht[bucket]->key = key;
}

int main() {
    char *data[] = {"acos", "atoi", "char", "define", "exp", "ceil", "cos", "float", "floor", "ctime"};
    for(int i=0; i<10; i++) insertDouble(data[i]);
    
    for(int i=0; i<MAX; i++) {
        printf("[%d]: ", i);
        if(ht[i]) printf("%s", ht[i]->item);
        printf("\n");
    }
    return 0;
}