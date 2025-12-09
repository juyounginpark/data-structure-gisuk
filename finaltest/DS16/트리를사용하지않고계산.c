/*
 * [변형 문제 3]
 * 이진 트리를 생성하지 않고, postfix 문자열과 변수값(a,b,c)을 입력받아
 * 스택(Stack)만을 사용하여 수식의 결과를 반환하는 evalPostfixDirect 함수를 작성하라.
 */
int evalPostfixDirect(char* postfix, int a, int b, int c) {
    int evalStack[100];
    int top = -1;
    int len = strlen(postfix);
    
    for(int i=0; i<len; i++) {
        char ch = postfix[i];
        if(ch == 'a') evalStack[++top] = a;
        else if(ch == 'b') evalStack[++top] = b;
        else if(ch == 'c') evalStack[++top] = c;
        else if(ch == '&') {
            int y = evalStack[top--];
            int x = evalStack[top--];
            evalStack[++top] = x && y;
        }
        else if(ch == '|') {
            int y = evalStack[top--];
            int x = evalStack[top--];
            evalStack[++top] = x || y;
        }
        else if(ch == '~') {
            int x = evalStack[top--];
            evalStack[++top] = !x;
        }
    }
    return evalStack[top];
}