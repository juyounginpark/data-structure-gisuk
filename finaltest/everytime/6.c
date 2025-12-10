/*해싱 (Division, String Key, Chaining)
요구사항: 문자열 키를 정수로 변환하고, 제산(Division) 함수와 체이닝(Chaining)을 사용하여 저장 및 탐색하시오.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 7 // 소수(Prime Number) 권장

// 체이닝을 위한 노드 구조체
typedef struct Node {
    char key[20];
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

// 1. 문자열 키를 정수로 변환 (Converting Keys to Integers)
int transform(char *key) {
    int number = 0;
    while (*key) {
        number += *key++; // 문자의 ASCII 값을 모두 더함
    }
    return number;
}

// 2. 제산 함수 (Division Method)
int hashFunction(char *key) {
    return transform(key) % TABLE_SIZE;
}

// 체이닝 삽입
void insert(char *key) {
    int hashValue = hashFunction(key);
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->next = NULL;

    // 해당 버킷의 맨 앞에 삽입 (Linked List Head Insert)
    if (hashTable[hashValue] == NULL) {
        hashTable[hashValue] = newNode;
    } else {
        newNode->next = hashTable[hashValue];
        hashTable[hashValue] = newNode;
    }
    printf("Inserted [%s] at index %d\n", key, hashValue);
}

// 자료 탐색
void search(char *key) {
    int hashValue = hashFunction(key);
    Node* curr = hashTable[hashValue];
    int count = 1;

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            printf("Found [%s] at index %d (depth: %d)\n", key, hashValue, count);
            return;
        }
        curr = curr->next;
        count++;
    }
    printf("[%s] not found\n", key);
}

// 테이블 출력
void printTable() {
    printf("\n--- Hash Table ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node* curr = hashTable[i];
        while (curr) {
            printf("%s -> ", curr->key);
            curr = curr->next;
        }
        printf("NULL\n");
    }
    printf("------------------\n");
}

int main() {
    // 초기화
    for (int i = 0; i < TABLE_SIZE; i++) hashTable[i] = NULL;

    // 데이터 삽입
    insert("apple");
    insert("banana");
    insert("grape");
    insert("melon");
    insert("orange"); // 충돌 발생 가능성 있음

    printTable();

    // 탐색
    printf("\nSearch Results:\n");
    search("melon");
    search("kiwi");

    return 0;
}
