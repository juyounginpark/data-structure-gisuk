/*
2025002720
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100
typedef struct node *tp;
typedef struct node {
    char d;
    tp l, r;
} n;

tp st[MAX];
int top=-1;
char e[81];

void push(tp p){st[++top]=p;}
tp pop(){return st[top--];}
tp newN(char d){
    tp p=(tp)malloc(sizeof(n));
    p->d=d;p->l=p->r=NULL;
    return p;
}

tp create(){
    FILE *f=fopen("input.txt","r");
    fgets(e,81,f);fclose(f);
    tp p;
    for(int i=0;e[i]&&e[i]!='\n';i++){
        if(isalpha(e[i])) push(newN(e[i]));
        else{
            p=newN(e[i]);
            p->r=pop();p->l=pop();
            push(p);
        }
    }
    return pop();
}

void in(tp p){if(p){in(p->l);printf("%c",p->d);in(p->r);}}
void pre(tp p){if(p){printf("%c",p->d);pre(p->l);pre(p->r);}}
void post(tp p){if(p){post(p->l);post(p->r);printf("%c",p->d);}}

int main(){
    tp r=create();
    in(r);printf("\n");
    pre(r);printf("\n");
    post(r);printf("\n");
}
