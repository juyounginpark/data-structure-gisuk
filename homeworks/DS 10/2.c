/*
	2025002720 박주영
	본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80

int top = -1;
FILE *fout;

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;

int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

char expr[MAX_EXPR_SIZE];
precedence stack[MAX_STACK_SIZE];

void push(precedence item) 
{
    stack[++top] = item;
}

int pop() 
{
    return stack[top--];
}

precedence getToken(char *symbol, int *n)
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
		case '(' : return lparen;
		case ')' : return rparen;
		case '+' : return plus;
		case '-' : return minus;
		case '/' : return divide;
		case '*' : return times;
		case '%' : return mod;
		case '\0': return eos;
		default : return operand;
	}
}

void printToken(precedence token) {
    switch (token) {
		case lparen : 
            fprintf(fout, "(");
            putchar('(');
            return;
        case rparen : 
            fprintf(fout, ")");
            putchar(')');
            return;
        case plus : 
            fprintf(fout, "+");
            putchar('+');
            return;
        case minus : 
            fprintf(fout, "-");
            putchar('-');
            return;
        case divide : 
            fprintf(fout, "/");
            putchar('/');
            return;
        case times : 
            fprintf(fout, "*");
            putchar('*');
            return;
        case mod : 
            fprintf(fout, "%%");
            putchar('%');
            return;
        case eos : 
            putchar('\0');
            return;
	}
}

void postfix(void)
{
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
        if (token == operand) {
            printf("%c", symbol);
            fprintf(fout, "%c", symbol);
        }
        else if (token == rparen) {
            while(stack[top] != lparen)
                printToken(pop());
            pop();
        }
        else {
            while(isp[stack[top]] >= icp[token])
                printToken(pop());
            push(token);
        }
    }
    while((token = pop()) != eos)
        printToken(token);
    printf("\n");
}

int main() {
    FILE *fp;
	int i = 0;
	if((fp = fopen("input.txt", "r")) == NULL) 
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	if((fout = fopen("output.txt", "w+")) == NULL) 
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%s", expr);
    puts("<<<<<<<<< infix to postfix >>>>>>>>>");

	printf("infix expression : ");
	for(int i = 0; expr[i]; i++) {
		printf("%c", expr[i]);
	}
	puts("");
	printf("postfix expression : ");
	postfix();

    fclose(fp);
    fclose(fout);
	return 0;
}