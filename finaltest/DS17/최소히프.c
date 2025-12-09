#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 200 // 히프의 최대 크기 정의

// 히프 요소를 저장할 구조체
typedef struct {
    int key;
} element;

element heap[MAX_ELEMENTS]; // 히프 배열 선언
int n = 0; // 현재 히프에 저장된 요소의 개수

// [최소 히프 삽입 함수]
// 부모 노드가 자식 노드보다 항상 작거나 같아야 합니다.
void pushMin(element item, int* n) {
    int i;
    // 1. 히프의 크기를 하나 증가시키고, 그 위치를 i로 설정 (말단 노드)
    i = ++(*n);

    // 2. 루트 노드가 아니고(i != 1), 
    //    삽입하려는 값(item)이 부모 노드(heap[i/2])보다 작다면 반복
    while ((i != 1) && (item.key < heap[i / 2].key)) {
        // 부모 노드의 값을 현재 자식 노드 위치(i)로 내림 (부모가 더 크므로)
        heap[i] = heap[i / 2];
        
        // 인덱스를 부모 위치로 이동하여 상위 레벨에서 비교 계속
        i /= 2;
    }
    
    // 3. 최종적으로 결정된 위치(i)에 새로운 값 삽입
    heap[i] = item;
}

// [최소 히프 삭제 함수]
// 가장 작은 값(루트)을 반환하고 히프를 재정렬합니다.
element popMin(int* n) {
    int parent, child;
    element item, temp;

    // 히프가 비어있으면 에러 반환
    if (*n == 0) {
        printf("Heap is empty\n");
        element err = { -1 }; 
        return err;
    }

    item = heap[1];      // 1. 루트 노드(최소값)를 저장해둠 (반환용)
    temp = heap[(*n)--]; // 2. 히프의 가장 마지막 요소를 가져오고 크기 감소

    parent = 1; // 루트에서 시작
    child = 2;  // 루트의 왼쪽 자식

    // 3. 자식 노드가 히프 범위 내에 있는 동안 반복
    while (child <= *n) {
        // 오른쪽 자식이 존재하고(child < *n), 
        // 왼쪽 자식보다 오른쪽 자식이 더 작다면(heap[child] > heap[child+1])
        // 더 작은 쪽으로 이동하기 위해 child 인덱스 증가
        if ((child < *n) && (heap[child].key > heap[child + 1].key)) {
            child++;
        }
        
        // 마지막 요소(temp)가 현재 비교 중인 자식(child)보다 작거나 같으면
        // 더 이상 내려갈 필요가 없으므로 반복 종료
        if (temp.key <= heap[child].key) break;

        // 자식 값이 더 작다면, 자식을 부모 위치로 올림
        heap[parent] = heap[child];
        
        // 한 단계 아래로 이동
        parent = child;
        child *= 2;
    }
    
    // 4. 찾은 위치에 마지막 요소를 저장
    heap[parent] = temp;
    
    return item; // 삭제된 최소값 반환
}

int main() {
    // 테스트 데이터
    int data[] = { 10, 40, 30, 5, 12 };
    
    printf("--- Min Heap Insertion ---\n");
    for (int i = 0; i < 5; i++) {
        element item = { data[i] };
        pushMin(item, &n);
        printf("Inserted %d\n", data[i]);
    }

    printf("\n--- Min Heap Array Status ---\n");
    // 배열 순서대로 출력 (레벨 순서)
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i].key);
    }
    printf("\n");
    
    printf("\n--- Pop Min (Delete Root) ---\n");
    element minVal = popMin(&n);
    printf("Popped Min Value: %d\n", minVal.key);
    
    printf("\n--- Array Status After Pop ---\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i].key);
    }
    printf("\n");

    return 0;
}