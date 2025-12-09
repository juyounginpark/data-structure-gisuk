/*
 * [변형 문제 4] Priority Queue Implementation
 *
 * [문제 설명]
 * Max Heap을 이용하여 우선순위 큐의 push(삽입)와 pop(최대값 삭제) 연산을 구현하시오.
 * 0은 종료, 1은 push, 2는 pop을 의미한다.
 *
 * [입력 예시]
 * 1 10
 * 1 20
 * 1 15
 * 2
 * 0
 *
 * [출력 예시]
 * 20 (pop된 값)
 */
#include <stdio.h>
#define MAX_SIZE 100

int heap[MAX_SIZE];
int n = 0;

void push(int item) {
    int i = ++n;
    while((i != 1) && (item > heap[i/2])) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = item;
}

int pop() {
    if(n == 0) return -1;
    int item = heap[1];
    int temp = heap[n--];
    int parent = 1, child = 2;
    while(child <= n) {
        if((child < n) && (heap[child] < heap[child+1])) child++;
        if(temp >= heap[child]) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}

int main() {
    int op, val;
    while(1) {
        scanf("%d", &op);
        if(op == 0) break;
        if(op == 1) { scanf("%d", &val); push(val); }
        else if(op == 2) printf("%d\n", pop());
    }
    return 0;
}