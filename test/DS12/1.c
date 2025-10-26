/*
2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
*/

#include <stdio.h>
#include <stdlib.h>

/*
 * 매크로 및 전역 선언
 */
#define MALLOC(p, s) \
    if(!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }

#define COMPARE(a, b) (a > b? 1 : (a==b ? 0 : -1))

/*
 * 구조체 정의
 */
typedef struct polyNode *polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
} polyNode;

/* 전역 변수 */
polyPointer a = NULL, b = NULL, c = NULL;

/*
 * 함수 원형 (프로토타입) 선언
 * (main 함수 위에 함수의 목록을 미리 선언합니다.)
 */
void inputPoly(char *filename, polyPointer *p);
void insert(polyPointer* first, polyPointer x, int co, int ex);
void find(polyPointer first, polyPointer *x);
polyPointer padd(polyPointer a, polyPointer b);
void attach(int coefficient, int exponent, polyPointer *ptr);
void printPoly(char *name, polyPointer first);
void erase(polyPointer *ptr);


/**
 * @brief 메인 함수
 * 프로그램의 전체 실행 흐름을 보여줍니다.
 */
int main() {
    // 1. "a.txt"와 "b.txt"에서 다항식을 읽어 리스트 a, b를 생성
    inputPoly("a.txt", &a);
    inputPoly("b.txt", &b);
    
    // 2. 읽어온 다항식 a와 b를 출력
    printPoly("a", a);
    printPoly("b", b);
    
    // 3. 다항식 a와 b를 더하여 리스트 c를 생성
    c = padd(a, b);
    
    // 4. 덧셈 결과인 다항식 c를 출력
    printPoly("a+b=c", c);
    
    // 5. 사용한 모든 메모리(리스트 a, b, c)를 해제
    erase(&a);
    erase(&b);
    erase(&c);
    
    return 0;
}


/*
 * 함수 정의
 * (main 함수 아래에 함수의 실제 구현 내용을 기술합니다.)
 */

/**
 * @brief 파일로부터 다항식을 읽어 내림차순 연결 리스트를 생성합니다.
 */
void inputPoly(char *filename, polyPointer *p) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    char type;
    fscanf(fp, "%c", &type); // 'a' 또는 'd'
    polyPointer x = NULL;
    int co, ex;
    
    if(type == 'a') {
        // 오름차순 입력 ('a'): 항상 리스트의 맨 앞에 삽입 (NULL 전달)
        while(fscanf(fp, "%d %d", &co, &ex) != EOF) {
            insert(p, NULL, co, ex);
        }
    }
    else {
        // 내림차순 입력 ('d'): 항상 리스트의 맨 뒤에 삽입
        while(fscanf(fp, "%d %d", &co, &ex) != EOF) {
            find(*p, &x); // x는 현재 리스트의 마지막 노드가 됨
            insert(p, x, co, ex);
        }
    }
    fclose(fp);
}

/**
 * @brief 리스트에 새 노드를 삽입합니다.
 * @param first 리스트의 시작 포인터 (주소)
 * @param x     삽입할 위치의 "앞" 노드. (NULL이면 맨 앞에 삽입)
 * @param co    계수
 * @param ex    지수
 */
void insert(polyPointer* first, polyPointer x, int co, int ex) {
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->coef = co;
    temp->expon = ex;

    if(*first == NULL) {
        // 1. 리스트가 비어있을 때 (x는 NULL이든 아니든 상관없음)
        temp->link = NULL;
        *first = temp;
    }
    else if(x == NULL) {
        // 2. 리스트가 비어있지 않고, 맨 앞에 삽입할 때 ('a' 타입)
        temp->link = *first;
        *first = temp;
    }
    else {
        // 3. 리스트가 비어있지 않고, x 노드 뒤에 삽입할 때 ('d' 타입)
        temp->link = x->link;
        x->link = temp;
    }
}

/**
 * @brief 리스트의 마지막 노드를 찾습니다.
 * @param first 리스트의 시작 포인터
 * @param x     찾은 마지막 노드를 저장할 포인터 (주소)
 */
void find(polyPointer first, polyPointer *x) {
    polyPointer pre = NULL;
    polyPointer trav = first;

    if(first == NULL) {
        // 리스트가 비어있으면
        *x = NULL;
    }
    else {
        // 리스트가 비어있지 않으면, 끝까지 탐색
        while(trav) {
            pre = trav;
            trav = trav->link;
        }
        *x = pre; // pre가 마지막 노드가 됨
    }
}

/**
 * @brief 두 다항식 a와 b를 더하여 c를 반환합니다.
 */
polyPointer padd(polyPointer a, polyPointer b)
{
    polyPointer c, rear, temp;
    int sum;
    MALLOC(rear, sizeof(*rear)); // 임시 헤더 노드 생성
    c = rear; // c는 헤더 노드를 가리킴

    // 1. a와 b에 모두 항이 남아있는 동안 비교
    while (a && b)
        switch (COMPARE(a->expon, b->expon))
        {
        case -1: // b의 지수가 더 큼
            attach(b->coef, b->expon, &rear);
            b = b->link;
            break;
        case 0: // 지수가 같음
            sum = a->coef + b->coef;
            if(sum) attach(sum, a->expon, &rear);
            a = a->link; b = b->link; 
            break;
        case 1: // a의 지수가 더 큼
            attach(a->coef, a->expon, &rear);
            a = a->link;
            break;
        }

    // 2. a 또는 b에 남은 항들을 모두 c의 뒤에 붙임
    for(; a; a = a->link) attach(a->coef, a->expon, &rear);
    for(; b; b = b->link) attach(b->coef, b->expon, &rear);
    rear->link = NULL;

    // 3. 임시 헤더 노드(c)를 제거하고 실제 시작 주소(c->link)를 반환
    temp = c; 
    c = c->link; 
    free(temp);
    return c;
}

/**
 * @brief 새 노드를 리스트의 *ptr(마지막 노드) 뒤에 연결합니다.
 */
void attach(int coefficient, int exponent, polyPointer *ptr)
{
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp; // 현재 마지막 노드(*ptr) 뒤에 새 노드 연결
    *ptr = temp;         // 마지막 노드 포인터를 새 노드로 업데이트
}

/**
 * @brief 다항식 리스트를 과제 형식에 맞게 출력합니다.
 */
void printPoly(char *name, polyPointer first) {
    printf("%-8s: ", name); // "a:", "b:", "a+b=c:" 정렬
    if (!first) {
        printf(" 0\n"); // 빈 리스트면 0 출력
        return;
    }

    polyPointer ptr = first;

    // 1. 첫 번째 항 처리
    if (ptr->coef > 0) {
        printf("+");
    }
    printf("%d", ptr->coef);

    if (ptr->expon > 1) {
        printf("x^%d", ptr->expon);
    } else if (ptr->expon == 1) {
        printf("x");
    }

    // 2. 두 번째 항부터 처리
    for (ptr = ptr->link; ptr; ptr = ptr->link) {
        if (ptr->coef > 0) {
            printf(" +");
        } else {
            printf(" ");
        }
        printf("%d", ptr->coef);
        
        if (ptr->expon > 1) {
            printf("x^%d", ptr->expon);
        } else if (ptr->expon == 1) {
            printf("x");
        }
    }
    puts(""); // 줄바꿈
}

/**
 * @brief 다항식 리스트(*ptr)의 모든 노드 메모리를 해제합니다.
 */
void erase(polyPointer *ptr)
{
    polyPointer temp;
    while(*ptr) {
        temp = *ptr;
        *ptr = (*ptr)->link; // 다음 노드로 이동
        free(temp);          // 현재 노드(temp) 삭제
    }
}