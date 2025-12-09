/*
 * [변형 문제 5] Iterative Chain Merge Sort
 *
 * [문제 설명]
 * 재귀 호출을 사용하지 않고, 반복문(Bottom-up)을 사용하여 link 배열 기반 합병 정렬을 구현하시오.
 * (길이가 1인 리스트들을 병합하여 2, 4, 8... 로 확장)
 *
 * [입력 예시]
 * 4
 * 4 3 2 1
 *
 * [출력 예시]
 * 1 2 3 4
 */
#include <stdio.h>
#define MAX_SIZE 100

typedef struct { int key; } element;
element a[MAX_SIZE];
int link[MAX_SIZE];
int n;

// listMerge 함수는 재사용 (위 정답 코드의 함수와 동일)
int listMerge(element a[], int link[], int start1, int start2); 
// (실제 컴파일 시 정답 코드의 listMerge 함수 본문을 여기에 포함해야 합니다)
// 편의상 이 예제 코드 내에서는 위 listMerge 로직이 존재한다고 가정합니다.
int listMergeImpl(element a[], int link[], int start1, int start2) {
     int last1 = start1, last2 = start2, lastResult = 0;
    while (last1 && last2) {
        if (a[last1].key <= a[last2].key) {
            link[lastResult] = last1; lastResult = last1; last1 = link[last1];
        } else {
            link[lastResult] = last2; lastResult = last2; last2 = link[last2];
        }
    }
    link[lastResult] = (last1 == 0) ? last2 : last1;
    return link[0];
}


// Bottom-up 방식은 배열 인덱스 관리가 복잡하여 
// 여기서는 개념적으로 인접한 두 체인을 병합하는 로직을 단순화하여 보여줍니다.
// 실제로는 큐(Queue)를 사용하여 정렬된 리스트의 헤드를 관리하는 것이 일반적입니다.

int main() {
    // 간단한 테스트를 위해 큐 대신 배열로 헤드 관리
    int heads[MAX_SIZE]; 
    scanf("%d", &n);
    for(int i=1; i<=n; i++) {
        scanf("%d", &a[i].key);
        link[i] = 0;
        heads[i-1] = i; // 초기에는 각 노드가 하나의 리스트 헤드
    }
    
    int listCount = n;
    while(listCount > 1) {
        int newCount = 0;
        for(int i=0; i < listCount; i += 2) {
            if (i + 1 < listCount) {
                // 두 리스트 병합
                heads[newCount++] = listMergeImpl(a, link, heads[i], heads[i+1]);
            } else {
                // 짝이 없는 마지막 리스트는 그대로 이동
                heads[newCount++] = heads[i];
            }
        }
        listCount = newCount;
    }
    
    int curr = heads[0];
    while(curr) {
        printf("%d ", a[curr].key);
        curr = link[curr];
    }
    return 0;
}