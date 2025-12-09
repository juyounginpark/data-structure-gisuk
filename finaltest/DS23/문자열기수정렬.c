/*
 * [변형 문제 3] Radix Sort for Fixed-Length Strings
 *
 * [문제 설명]
 * 길이가 3인 대문자 문자열들을 기수 정렬(LSD)로 정렬하시오.
 *
 * [입력 예시]
 * 3
 * CAT
 * BAT
 * ART
 *
 * [출력 예시]
 * ART BAT CAT
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char str[4]; } element;
element list[100];
int link[100];

int getCharIndex(char c) { return c - 'A'; } // 'A'=0, 'B'=1 ...

void radixSortStr(element a[], int link[], int n, int len) {
    int front[26], rear[26];
    int first = 1;
    for(int i=1; i<n; i++) link[i] = i+1; link[n] = 0;

    for(int i=len-1; i>=0; i--) { // LSD: 뒤에서부터
        for(int j=0; j<26; j++) front[j] = rear[j] = 0;
        
        for(int curr=first; curr; curr=link[curr]) {
            int bin = getCharIndex(a[curr].str[i]);
            if(front[bin]==0) front[bin] = curr;
            else link[rear[bin]] = curr;
            rear[bin] = curr;
        }

        int bin;
        for(bin=0; !front[bin]; bin++);
        first = front[bin];
        int last = rear[bin];

        for(bin++; bin<26; bin++) {
            if(front[bin]) {
                link[last] = front[bin];
                last = rear[bin];
            }
        }
        link[last] = 0;
    }
    
    int curr = first;
    while(curr) { printf("%s ", a[curr].str); curr = link[curr]; }
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%s", list[i].str);
    radixSortStr(list, link, n, 3);
    return 0;
}