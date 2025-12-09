/*
 * [변형 문제 4] Rehashing (Dynamic Resizing)
 *
 * [문제 설명]
 * 데이터 개수가 테이블 크기의 70%를 넘으면 테이블 크기를 2배(정확히는 소수)로 늘리고 재해싱하시오.
 * (여기선 간단히 2배+1로 구현)
 *
 * [입력 예시]
 * (데이터 10개 삽입)
 *
 * [출력 예시]
 * Table resized from 11 to 23
 * (재해싱된 테이블 상태)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 10

typedef struct { char item[MAX_CHAR]; int key; } element;
element** ht;
int TABLE_SIZE = 11;
int count = 0;

unsigned int stringToInt(char *key) {
    int number = 0; while (*key) number += *key++; return number;
}

void insertRaw(element** table, int size, char* str, int key) {
    int bucket = key % size;
    while (table[bucket] != NULL) bucket = (bucket + 1) % size;
    table[bucket] = (element*)malloc(sizeof(element));
    strcpy(table[bucket]->item, str); table[bucket]->key = key;
}

void rehash() {
    int oldSize = TABLE_SIZE;
    TABLE_SIZE = TABLE_SIZE * 2 + 1; // 새 크기
    element** newHt = (element**)calloc(TABLE_SIZE, sizeof(element*));
    
    for(int i=0; i<oldSize; i++) {
        if(ht[i]) insertRaw(newHt, TABLE_SIZE, ht[i]->item, ht[i]->key);
    }
    free(ht);
    ht = newHt;
    printf(">> Table Resized: %d -> %d\n", oldSize, TABLE_SIZE);
}

void insert(char *str) {
    if ((float)(count + 1) / TABLE_SIZE > 0.7) rehash();
    insertRaw(ht, TABLE_SIZE, str, stringToInt(str));
    count++;
}

int main() {
    ht = (element**)calloc(TABLE_SIZE, sizeof(element*));
    char *data[] = {"acos", "atoi", "char", "define", "exp", "ceil", "cos", "float", "floor", "ctime"};
    for(int i=0; i<10; i++) insert(data[i]);
    
    for(int i=0; i<TABLE_SIZE; i++) {
        if(ht[i]) printf("[%d]: %s\n", i, ht[i]->item);
    }
    return 0;
}