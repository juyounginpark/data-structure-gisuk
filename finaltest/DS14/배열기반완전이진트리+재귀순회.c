/*
[변형 문제 5]
완전이진트리를 연결 구조(struct node + 포인터)가 아닌 배열로 표현하려고 한다.
배열 tree[ ] 에 다음과 같이 문자를 저장한다.

인덱스 1이 루트라고 할 때,
왼쪽 자식의 인덱스는 2*i, 오른쪽 자식의 인덱스는 2*i + 1 이다.

예를 들어, 입력이 ABCDEFG 이라면
tree[1] = 'A'
tree[2] = 'B'
tree[3] = 'C'
tree[4] = 'D'
tree[5] = 'E'
tree[6] = 'F'
tree[7] = 'G'

(1) 문자열을 입력 받아 위와 같은 배열 기반 완전이진트리를 구성한다.
(2) 재귀 함수를 이용하여 중위순회, 전위순회, 후위순회를 각각 출력한다.

2024002779 김시연
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

char tree[MAX_SIZE];
int n; // 실제 사용되는 노드 수

void inorder(int idx) {
    if (idx > n) return;
    inorder(idx * 2);
    printf("%c", tree[idx]);
    inorder(idx * 2 + 1);
}

void preorder(int idx) {
    if (idx > n) return;
    printf("%c", tree[idx]);
    preorder(idx * 2);
    preorder(idx * 2 + 1);
}

void postorder(int idx) {
    if (idx > n) return;
    postorder(idx * 2);
    postorder(idx * 2 + 1);
    printf("%c", tree[idx]);
}

int main() {
    char input[MAX_SIZE];

    if (scanf("%s", input) != 1) return 0;
    n = (int)strlen(input);

    // 1번 인덱스부터 채우기
    for (int i = 0; i < n; i++) {
        tree[i + 1] = input[i];
    }

    printf("Inorder  : ");
    inorder(1);
    printf("\n");

    printf("Preorder : ");
    preorder(1);
    printf("\n");

    printf("Postorder: ");
    postorder(1);
    printf("\n");

    return 0;
}
