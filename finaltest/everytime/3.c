/*문제 3] Hashing: Slot 크기 2배로 확장 (Rehashing)
핵심 요구사항:

데이터 삽입 중 특정 조건(Load Factor)이 차면 테이블 크기를 2배로 늘림.

중요: 크기가 바뀌면 key % new_size로 인덱스가 바뀌므로, 모든 데이터를 다시 해싱해서 옮겨야 합니다.*/

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 5
#define LOAD_FACTOR_THRESHOLD 0.7 // 70% 차면 확장

typedef struct {
    int key;
    int value; // 편의상 value도 int
    int is_occupied; // 슬롯 사용 여부 (0: 빈곳, 1: 사용중)
} Slot;

typedef struct {
    Slot* buckets;
    int size;  // 현재 슬롯 크기
    int count; // 저장된 데이터 개수
} HashTable;

// 해시 테이블 초기화
void initTable(HashTable* ht, int size) {
    ht->size = size;
    ht->count = 0;
    ht->buckets = (Slot*)malloc(sizeof(Slot) * size);
    for (int i = 0; i < size; i++) ht->buckets[i].is_occupied = 0;
}

// 해시 함수
int hashFunction(int key, int size) {
    return key % size;
}

// 내부 삽입 함수 (재해싱 때도 쓰임)
void insertInternal(Slot* buckets, int size, int key, int value) {
    int idx = hashFunction(key, size);
    // 선형 조사법 (Linear Probing)으로 빈칸 찾기
    while (buckets[idx].is_occupied) {
        idx = (idx + 1) % size;
    }
    buckets[idx].key = key;
    buckets[idx].value = value;
    buckets[idx].is_occupied = 1;
}

// 재해싱 (Rehashing) - 크기 2배 확장
void rehash(HashTable* ht) {
    int oldSize = ht->size;
    int newSize = oldSize * 2;
    Slot* oldBuckets = ht->buckets;

    printf("\n[Resize Triggered] Expanding table from %d to %d...\n", oldSize, newSize);

    // 새 버킷 할당
    Slot* newBuckets = (Slot*)malloc(sizeof(Slot) * newSize);
    for (int i = 0; i < newSize; i++) newBuckets[i].is_occupied = 0;

    // 기존 데이터 -> 새 버킷으로 이동 (Rehashing)
    for (int i = 0; i < oldSize; i++) {
        if (oldBuckets[i].is_occupied) {
            insertInternal(newBuckets, newSize, oldBuckets[i].key, oldBuckets[i].value);
        }
    }

    free(oldBuckets); // 기존 메모리 해제
    ht->buckets = newBuckets;
    ht->size = newSize;
}

// 사용자용 삽입 함수
void insert(HashTable* ht, int key, int value) {
    // 적재율 검사 및 리사이징
    if ((double)(ht->count + 1) / ht->size > LOAD_FACTOR_THRESHOLD) {
        rehash(ht);
    }

    insertInternal(ht->buckets, ht->size, key, value);
    ht->count++;
    printf("Inserted key %d (Table size: %d, Count: %d)\n", key, ht->size, ht->count);
}

void printTable(HashTable* ht) {
    printf("--- Table Status (Size: %d) ---\n", ht->size);
    for (int i = 0; i < ht->size; i++) {
        if (ht->buckets[i].is_occupied)
            printf("[%d]: %d \n", i, ht->buckets[i].key);
        else
            printf("[%d]: - \n", i);
    }
    printf("-------------------------------\n");
}

int main() {
    HashTable ht;
    initTable(&ht, INITIAL_SIZE); // 초기 크기 5

    // 데이터 삽입 (초기 크기가 5이므로, 4번째 넣을 때 리사이징 예상)
    insert(&ht, 10, 100);
    insert(&ht, 20, 200);
    insert(&ht, 30, 300);
    printTable(&ht);

    // 여기서 Load Factor > 0.7 발생 -> 크기 10으로 2배 확장
    insert(&ht, 40, 400); 
    
    insert(&ht, 55, 550);
    printTable(&ht); // 확장된 결과 확인 (키 10, 20... 등의 인덱스가 바뀜)

    return 0;
}