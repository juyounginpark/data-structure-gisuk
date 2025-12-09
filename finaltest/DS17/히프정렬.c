#include <stdio.h>

#define MAX_ELEMENTS 200

typedef struct {
    int key;
} element;

element heap[MAX_ELEMENTS];
int n = 0;

// [최대 히프 삽입] - 정렬을 위한 보조 함수
void pushMax(element item, int* n) {
    int i;
    i = ++(*n);
    // 부모보다 내가 더 크면 부모를 내림 (Max Heap 조건)
    while ((i != 1) && (item.key > heap[i / 2].key)) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = item;
}

// [최대 히프 삭제] - 정렬을 위한 보조 함수
element popMax(int* n) {
    int parent, child;
    element item, temp;
    item = heap[1];      // 최대값(루트) 백업
    temp = heap[(*n)--]; // 마지막 노드 가져옴
    parent = 1;
    child = 2;
    
    while (child <= *n) {
        // 더 큰 자식을 선택 (왼쪽 vs 오른쪽)
        if ((child < *n) && (heap[child].key < heap[child + 1].key))
            child++;
        // 마지막 노드가 자식보다 크면 위치 확정
        if (temp.key >= heap[child].key) break;
        
        heap[parent] = heap[child]; // 자식을 위로 올림
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}

// [히프 정렬 함수]
void heapSort(int arr[], int size) {
    int heapCount = 0; // 로컬 히프 카운터
    
    // 1단계: 배열의 모든 원소를 최대 히프에 삽입
    for(int i = 0; i < size; i++) {
        element item;
        item.key = arr[i];
        pushMax(item, &heapCount);
    }
    
    // 2단계: 히프에서 하나씩 꺼내어 배열의 뒷부분부터 채움
    // Max Heap에서 pop하면 가장 큰 값이 나오므로, 
    // 맨 뒤(size-1)부터 채워야 오름차순(1, 2, 3...)이 됨
    for(int i = size - 1; i >= 0; i--) {
        element maxNode = popMax(&heapCount);
        arr[i] = maxNode.key;
    }
}

int main() {
    int data[] = { 60, 10, 40, 30, 5, 12, 6, 15, 9 };
    int size = sizeof(data) / sizeof(data[0]);

    printf("Before Sort: ");
    for(int i=0; i<size; i++) printf("%d ", data[i]);
    printf("\n");

    // 정렬 수행
    heapSort(data, size);

    printf("After Sort : ");
    for(int i=0; i<size; i++) printf("%d ", data[i]);
    printf("\n");

    return 0;
}