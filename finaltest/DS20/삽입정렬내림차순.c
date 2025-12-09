/*
 * [변형 문제 3] Insertion Sort (Descending)
 *
 * [문제 설명]
 * 삽입 정렬을 이용하여 데이터를 내림차순으로 정렬하시오.
 *
 * [입력 예시]
 * 5
 * 10 30 20 50 40
 *
 * [출력 예시]
 * 50 40 30 20 10
 */

#include <stdio.h>

void insertionSortDesc(int a[], int n) {
    int j;
    // 1-based indexing 사용
    for (j = 2; j <= n; j++) {
        int temp = a[j];
        int i = j - 1;
        // 오름차순과 반대로, temp가 앞의 값보다 크면 앞의 값을 뒤로 밀어냄
        while (i >= 1 && temp > a[i]) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = temp;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int a[100]; // a[0]은 미사용 혹은 sentinel (여기선 while조건으로 제어)
    
    for(int i=1; i<=n; i++) scanf("%d", &a[i]);

    insertionSortDesc(a, n);

    for(int i=1; i<=n; i++) printf("%d ", a[i]);
    return 0;
}