/*
 * [문제] 자료구조응용 24: Static Hashing (Linear Probing)
 *
 * [문제 설명]
 * 입력 파일(input.txt)로부터 문자열을 읽어 해시 테이블에 저장하고,
 * 사용자로부터 문자열을 입력받아 탐색하는 프로그램을 작성하시오.
 * - 해시 함수: 문자열의 각 문자의 아스키 코드 합 % 11
 * - 충돌 처리: Linear Probing (선형 조사법)
 * - 테이블 크기: 11 (MAX)
 *
 * [입력 예시 (input.txt)]
 * acos atoi char define exp ceil cos float floor ctime
 *
 * [출력 예시]
 * input strings: acos atoi char ...
 *
 * item       key
 * ht[0]: atoi       429
 * ht[1]:
 * ht[2]: ctime      530
 * ...
 * string to search >> floor
 * item: floor, key: 546, the number of comparisons: 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 11
#define MAX_CHAR 10

typedef struct {
    char item[MAX_CHAR];
    int key;
} element;

element* ht[MAX]; // 해시 테이블 (포인터 배열)

// Program 8.1: String to Integer conversion
unsigned int stringToInt(char *key) {
    int number = 0;
    while (*key)
        number += *key++;
    return number;
}

// 해시 함수: k % b
int h(int k) {
    return k % MAX;
}

// Insert 함수 (Linear Probing)
void insert(char *str) {
    int key = stringToInt(str);
    int homeBucket = h(key);
    int currentBucket = homeBucket;

    // Linear Probing으로 빈 슬롯 찾기
    while (ht[currentBucket] != NULL) {
        if (strcmp(ht[currentBucket]->item, str) == 0) {
            printf("Duplicate key error: %s\n", str);
            return;
        }
        currentBucket = (currentBucket + 1) % MAX;
        if (currentBucket == homeBucket) {
            printf("Hash table is full!\n");
            return;
        }
    }

    // 새 요소 할당 및 저장
    element *newElem = (element*)malloc(sizeof(element));
    strcpy(newElem->item, str);
    newElem->key = key;
    ht[currentBucket] = newElem;
}

// Search 함수 (탐색 및 비교 횟수 반환)
element* search(char *str, int *comparisons) {
    int key = stringToInt(str);
    int homeBucket = h(key);
    int currentBucket = homeBucket;
    *comparisons = 0;

    while (ht[currentBucket] != NULL) {
        (*comparisons)++;
        if (strcmp(ht[currentBucket]->item, str) == 0) { // 키 비교 대신 문자열 비교
            return ht[currentBucket];
        }
        currentBucket = (currentBucket + 1) % MAX;
        if (currentBucket == homeBucket) return NULL;
    }
    return NULL;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    char buffer[MAX_CHAR];

    if (fp == NULL) {
        printf("input.txt not found.\n");
        // 파일 없으면 예제 데이터 사용 (테스트용)
        char *data[] = {"acos", "atoi", "char", "define", "exp", "ceil", "cos", "float", "floor", "ctime"};
        printf("input strings:");
        for(int i=0; i<10; i++) {
            printf(" %s", data[i]);
            insert(data[i]);
        }
        printf("\n");
    } else {
        printf("input strings:");
        while (fscanf(fp, "%s", buffer) != EOF) {
            printf(" %s", buffer);
            insert(buffer);
        }
        printf("\n");
        fclose(fp);
    }

    printf("\n\titem\tkey\n");
    for (int i = 0; i < MAX; i++) {
        printf("ht[%d]:\t", i);
        if (ht[i]) printf("%s\t%d", ht[i]->item, ht[i]->key);
        printf("\n");
    }

    printf("\nstring to search >> ");
    scanf("%s", buffer);

    int comps = 0;
    element *found = search(buffer, &comps);

    if (found) {
        printf("item: %s, key: %d, the number of comparisons: %d\n", found->item, found->key, comps);
    } else {
        printf("it doesn't exist!\n");
    }

    return 0;
}