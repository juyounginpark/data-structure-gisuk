/*
 * [변형 문제 4] Insertion Sort by Name (String)
 *
 * [문제 설명]
 * 학생들의 정보를 입력받아 이름(사전 순)으로 삽입 정렬하시오.
 *
 * [입력 예시]
 * 3
 * 10 Lee 90
 * 20 Kim 80
 * 30 Park 95
 *
 * [출력 예시]
 * 20 Kim 80
 * 10 Lee 90
 * 30 Park 95
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    int key;
    char name[20];
    int grade;
} element;

void insertionSortByName(element a[], int n) {
    int j;
    // 0번 인덱스는 sentinel로 활용하기 위해 비워둠 (1-based)
    for (j = 2; j <= n; j++) {
        element temp = a[j];
        int i = j - 1;
        // strcmp(A, B) > 0 이면 A가 B보다 뒤에 있음 -> 오름차순 정렬을 위해 밀어냄
        while (i >= 1 && strcmp(a[i].name, temp.name) > 0) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = temp;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    element a[100];
    
    for(int i=1; i<=n; i++) 
        scanf("%d %s %d", &a[i].key, a[i].name, &a[i].grade);

    insertionSortByName(a, n);

    for(int i=1; i<=n; i++) 
        printf("%d %s %d\n", a[i].key, a[i].name, a[i].grade);
    return 0;
}