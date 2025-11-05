/*
2025002720
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *left, *right;
} node;

node *stack[100];
int top = -1;
char expr[100];

void push(node *n) { stack[++top] = n; }
node* pop() { return stack[top--]; }

node* createNode(char c) {
    node *n = (node*)malloc(sizeof(node));
    n->data = c;
    n->left = n->right = NULL;
    return n;
}

node* makeTree() {
    char c;
    int i = 0;
    while ((c = expr[i++]) != '\0' && c != '\n') {
        node *t = createNode(c);
        if (c == '&' || c == '|') {
            t->right = pop();
            t->left = pop();
            push(t);
        }
        else if (c == '~') {
            t->right = pop();
            push(t);
        }
        else push(t);
    }
    return pop();
}

void inorder(node *root) {
    if (!root) return;
    if (root->left || root->right) printf("(");
    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);
    if (root->left || root->right) printf(")");
}

int eval(node *root, int a, int b, int c) {
    if (!root) return 0;
    switch (root->data) {
    case 'a': return a;
    case 'b': return b;
    case 'c': return c;
    case '&': return eval(root->left, a, b, c) && eval(root->right, a, b, c);
    case '|': return eval(root->left, a, b, c) || eval(root->right, a, b, c);
    case '~': return !eval(root->right, a, b, c);
    default: return 0;
    }
}

int main(void) {
    FILE *fp = fopen("postfix.txt", "r");
    if (!fp) {
        fprintf(stderr, "cannot open postfix.txt\n");
        exit(EXIT_FAILURE);
    }
    fgets(expr, 100, fp);
    fclose(fp);

    printf("************ satisfiability problem ************\n");
    printf("Note: For efficiency, &, |, ~ are used instead of\n");
    printf("logical and(&&), logical or(||), logical not(!)\n");
    printf("***********************************************\n");
    printf("input string(postfix)   : %s\n", expr);

    printf("\ncreating binary tree for satisfiability algorithm...\n");
    node *root = makeTree();

    printf("inorder traversal       : ");
    inorder(root);
    printf("\n\nfor all combinations of (a, b, c)...\n");

    for (int a = 1; a >= 0; a--) {
        for (int b = 1; b >= 0; b--) {
            for (int c = 1; c >= 0; c--) {
                int res = eval(root, a, b, c);
                printf("(%c, %c, %c) is %s\n",
                    a ? 't' : 'f',
                    b ? 't' : 'f',
                    c ? 't' : 'f',
                    res ? "TRUE" : "FALSE");
            }
        }
    }
    return 0;
}

