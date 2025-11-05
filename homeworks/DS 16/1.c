/*
2025002720
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef enum { lparen, rparen, or, and, not, eos, operand } precedence;

int isp[] = { 0, 19, 1, 3, 7, 0, 0 };
int icp[] = { 20, 19, 1, 3, 7, 0, 0 };

void postfix(void);
precedence getToken(char *symbol, int *n);
void printToken(precedence token);
void push(precedence item);
precedence pop();
void stackFull();
precedence stackEmpty();

precedence stack[MAX_STACK_SIZE];
int top = -1;
char expr[81];
FILE *fpI, *fpP;

int main(void)
{
    if (!(fpI = fopen("infix.txt", "r")) || !(fpP = fopen("postfix.txt", "w"))) {
        fprintf(stderr, "cannot open the file\n");
        exit(EXIT_FAILURE);
    }

    fgets(expr, 80, fpI);
    printf("<<<<<<<<<< infix to postfix >>>>>>>>>>>>>\n");
    printf("infix expression\t: %s\n", expr);
    printf("postfix expression\t: ");

    postfix();

    fclose(fpI);
    fclose(fpP);
    return 0;
}

void postfix(void)
{
    char symbol;
    precedence token;
    int n = 0;
    top = -1;
    stack[++top] = eos;

    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
        if (token == operand) {
            printf("%c", symbol);
            fprintf(fpP, "%c", symbol);
        } else if (token == rparen) {
            while (stack[top] != lparen)
                printToken(pop());
            pop();
        } else {
            while (isp[stack[top]] >= icp[token])
                printToken(pop());
            push(token);
        }
    }

    while ((token = pop()) != eos)
        printToken(token);
    printf("\n");
}

precedence getToken(char *symbol, int *n)
{
    *symbol = expr[(*n)++];
    switch (*symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '&': return and;
    case '|': return or;
    case '~': return not;
    case '\0':
    case '\n': return eos;
    default: return operand;
    }
}

void printToken(precedence token)
{
    switch (token) {
    case and: printf("&"); fprintf(fpP, "&"); break;
    case or: printf("|"); fprintf(fpP, "|"); break;
    case not: printf("~"); fprintf(fpP, "~"); break;
    default: break;
    }
}

void push(precedence item)
{
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

precedence pop()
{
    if (top == -1)
        return stackEmpty();
    return stack[top--];
}

void stackFull()
{
    fprintf(stderr, "stack is full\n");
    exit(EXIT_FAILURE);
}

precedence stackEmpty()
{
    fprintf(stderr, "stack is empty\n");
    exit(EXIT_FAILURE);
}

