/*
    2025202720 박주영
    본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 100

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct {
    int id;
    char name[MAX_NAME_SIZE];
} element;

// 전역 변수
element* queue;
int capacity = 2;
int rear = 0;
int front = 0;

// 함수 선언
void addq(element item);
element deleteq();
void queueFull();
element queueEmpty();
void copy(element* a, element* b, element* c);

int main() {
    MALLOC(queue, capacity * sizeof(element));
    
    char input[80];
    char* delimiter = " \n";
    char* op = NULL;
    element student;

    puts("<< circular queue operations where the initial capacity is 2 >>");
    puts("add 1 Jung");
    puts("delete");
    puts("*******************************************");

    while (1) {
        fgets(input, sizeof(input), stdin);
        op = strtok(input, delimiter);

        if (!strcmp(op, "add")) {
            sscanf(input + strlen(op) + 1, "%d%s", &student.id, student.name);
            addq(student);
        }
        else if (!strcmp(op, "delete")) {
            element item = deleteq();
            if (item.id == -1) 
                exit(EXIT_FAILURE);
            printf("deleted item : %d %s\n", item.id, item.name);
        }
        else if (!strcmp(op, "quit")) 
            break;
        else 
            puts("wrong command! try again");
    }

    free(queue);
    return 0;
}

void addq(element item) {
    rear = (rear + 1) % capacity;
    if (front == rear)
        queueFull();
    queue[rear] = item;
}

element deleteq() {
    if (front == rear)
        return queueEmpty();

    front = (front + 1) % capacity;
    return queue[front];
}

void queueFull() {
    element* newQueue;
    MALLOC(newQueue, 2 * capacity * sizeof(element));

    int start = (front + 1) % capacity;
    rear--;
    
    if (start < 2) {
        copy(queue + start, queue + start + capacity - 1, newQueue);
    }
    else {
        copy(queue + start, queue + capacity, newQueue);
        copy(queue, queue + rear + 1, newQueue + capacity - start);
    }

    front = 2 * capacity - 1;
    rear = capacity - 1;
    capacity *= 2;
    
    free(queue);
    queue = newQueue;
    
    puts("queue capacity is doubled,");
    printf("current queue capacity is %d\n", capacity);
}

void copy(element* a, element* b, element* c) {
    while (a != b)
        *c++ = *a++;
}

element queueEmpty() {
    element err = {-1, ""};
    puts("queue is empty, cannot delete element.");
    return err;
}