/*
	2025002720 박주영
	본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80

int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top = -1;

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;

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

void push(int item) 
{
    stack[++top] = item;
}

int pop() 
{
    return stack[top--];
}

int eval(void) 
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand) 
			push(symbol-'0');
		else {
			op2 = pop();
			op1 = pop();
			switch (token)
			{
			case plus:
				push(op1+op2);
				break;
			case minus:
				push(op1-op2);
				break;
			case times:
				push(op1*op2);
				break;
			case divide:
				push(op1/op2);
				break;
			case mod:
				push(op1%op2);
			}
		}
		token = getToken(&symbol, &n);
		
	}
	return pop(); 
}


int main() {
	FILE *fp;
	int i = 0;
	if((fp = fopen("input.txt", "r")) == NULL) 
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%s", expr);

	printf("postfix expression : ");
	for(int i = 0; expr[i]; i++) {
		printf("%c", expr[i]);
	}
	puts("");
	printf("the evaluation value : ");
	printf("%d\n", eval());

	return 0;

}
