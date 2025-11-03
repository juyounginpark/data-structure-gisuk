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

tp st[MAX]; int top=-1;
tp q[MAX]; int f=0,r=0;

void push(tp p){st[++top]=p;}
tp pop(){return st[top--];}
int sEmpty(){return top==-1;}
void en(tp p){q[r=(r+1)%MAX]=p;}
tp de(){f=(f+1)%MAX;return q[f];}
int qEmpty(){return f==r;}
tp newN(char d){tp p=(tp)malloc(sizeof(n));p->d=d;p->l=p->r=NULL;return p;}

tp create(){
    printf("the length of input string should be less than 80\n");
    printf("input string (postfix expression) : ");
    char e[81];scanf("%s", e);
    printf("creating its binary tree\n\n");
    tp p;
    for(int i=0;e[i];i++){
        if(isalpha(e[i])) push(newN(e[i]));
        else{p=newN(e[i]);p->r=pop();p->l=pop();push(p);}
    }
    return pop();
}

void iterIn(tp p){
    tp c=p;
    while(1){
        while(c){push(c);c=c->l;}
        if(sEmpty())break;
        c=pop();printf("%c",c->d);
        c=c->r;
    }
}

void iterPre(tp p){
    tp c=p;
    while(1){
        while(c){printf("%c",c->d);push(c);c=c->l;}
        if(sEmpty())break;
        c=pop();c=c->r;
    }
}

void level(tp p){
    if(!p)return;
    en(p);
    while(!qEmpty()){
        tp t=de();
        printf("%c",t->d);
        if(t->l)en(t->l);
        if(t->r)en(t->r);
    }
}

int main(){
    tp r=create();
    printf("iterative inorder traversal   : "); iterIn(r); printf("\n");
    printf("iterative preorder traversal  : "); iterPre(r); printf("\n");
    printf("level order traversal         : "); level(r); printf("\n");
}
