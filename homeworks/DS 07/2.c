/*
	2025002720 박주영
	본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define  MAX_STACK_SIZE 5
typedef struct {
    int id;
    char name[MAX_STACK_SIZE];
} element;

element stack[MAX_STACK_SIZE];
int top = -1;


element stackEmpty() {
    fprintf(stderr, "Stack is empty, cannot delete element");
    element err = { -1, "error"};
    return err;
}

element pop() 
{
    if (top == -1) return stackEmpty();
    return stack[top--];
}

void stackFull()
{
    puts("Stack is full, cannot add element");
    puts("current stack elements!");
    for(int i = top; i >= 0; i--) {
        element item;
        item = pop();
        printf("%d %s\n", item.id, item.name);
    }
    exit(EXIT_FAILURE);
}

void push(element item) 
{
    if (top >= MAX_STACK_SIZE-1) stackFull();
    stack[++top] = item;
}

int main() {
    char input[80];
    char *delimiter = " \n";
    char *op = NULL;
    element student;

    int cnt;

    puts("<< stack operations where MAX_STACK_SIZE is 5 >>");
    puts("push 1 jung");
    puts("pop");
    puts("=================================================");
    

    while(1) {
        fgets(input, sizeof(input), stdin);
        op = strtok(input, delimiter);

        if(!strcmp(op, "push"))
        {
            sscanf(input + strlen(op) + 1, "%d%s", &student.id, student.name);
            push(student);
        }
        else if(!strcmp(op, "pop"))
        {
            element item;
            item = pop();
            if (item.id == -1) exit(EXIT_FAILURE);
        }
        else if(!strcmp(op, "quit")) break;
        else printf("wrong command! try again\n");

    }

    return 0;

}