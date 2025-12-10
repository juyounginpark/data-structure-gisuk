/*최소 히프(Min Heap) 생성 및 순회
요구사항: 자료를 입력받아 최소 히프를 구성하고, Level Order(배열 순서 그대로)와 Postorder(트리 구조)를 출력하시오.*/
#include <stdio.h>

#define MAX_ELEMENT 100

typedef struct {
    int heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

void init(HeapType* h) {
    h->heap_size = 0;
}

// 최소 히프 삽입 (Min Heap Insert)
void insert_min_heap(HeapType* h, int item) {
    int i;
    i = ++(h->heap_size);

    // 부모가 현재 값보다 크면 부모를 아래로 내림 (작은 값이 위로 가도록)
    while ((i != 1) && (item < h->heap[i / 2])) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// 1. Level Order (히프는 배열 자체가 Level Order 순서임)
void levelOrder(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i]);
    }
}

// 2. Postorder (배열 인덱스를 이용한 재귀 순회)
void postorder(HeapType* h, int index) {
    if (index > h->heap_size) return;
    
    postorder(h, index * 2);     // Left Child
    postorder(h, index * 2 + 1); // Right Child
    printf("%d ", h->heap[index]); // Root
}

int main() {
    HeapType h;
    init(&h);
    
    // 예시 데이터 입력
    int data[] = { 50, 30, 20, 10, 40, 60 };
    int n = sizeof(data) / sizeof(int);

    printf("Inserting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
        insert_min_heap(&h, data[i]);
    }
    printf("\n\n");

    printf("Min Heap Level Order: ");
    levelOrder(&h);
    printf("\n");

    printf("Min Heap Postorder  : ");
    postorder(&h, 1); // 루트 인덱스 1부터 시작
    printf("\n");

    return 0;
}