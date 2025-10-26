/*
    2025202720 박주영
    본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef struct 
{
    int id;
    char name[MAX_QUEUE_SIZE];
}element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

element queueEmpty();

void addq(element);

element deleteq();

void queueFull();
int main() {
    char input[80];
    char *delimiter = " \n";
    char *op = NULL;
    element student;

    puts("<< linear queue operations where MAX_QUEUE_SIZE is 5>>");
    puts("add 1 Jung");
    puts("delete");
    puts("************************************");

    while(1) {
        fgets(input, sizeof(input), stdin);
        op = strtok(input, delimiter);
        
        if(!strcmp(op, "add"))
        {
            sscanf(input + strlen(op) + 1, "%d%s", &student.id, student.name);
            addq(student);
        }
        else if(!strcmp(op, "delete"))
        {
            element item;
            item = deleteq();
            if (item.id == -1) exit(EXIT_FAILURE);
        }
        else if(!strcmp(op, "quit")) break;
        else puts("wrong command! try again");

    }

}

element queueEmpty() {
    element err = {-1,};
    puts("queue is empty, cannot delete element.");
    return err;
}

void addq(element item)
{
    if (rear == MAX_QUEUE_SIZE-1)
        queueFull();
    queue[++rear] = item;
}

element deleteq()
{
    if (front == rear)
        return queueEmpty();
    return queue[++front];
}

void queueFull()
{
    if(front == -1) {
        puts("Queue is full, cannot add element");
        puts("current queue elements :");
        element now;
        for(int i = 0; i <= rear; i++) {
            now = deleteq();
            printf("%d %s\n", now.id, now.name);
        }
        exit(EXIT_FAILURE);
    }

    puts("array shifting...");
    
    int temp = rear - front;
    rear = -1;
    element now;
    for(int i = 0; i < temp; i++) {
        now = deleteq();
        addq(now);
    }
    front = -1;
   
    return;

}