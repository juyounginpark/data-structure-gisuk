/*
 * [변형 문제 5] Radix Sort with Negatives
 *
 * [문제 설명]
 * 음수가 포함된 배열을 기수 정렬하시오.
 * (모든 수에 최솟값의 절댓값을 더해 양수로 변환 후 정렬하고 다시 복원하는 방식 사용)
 *
 * [입력 예시]
 * 5
 * -5 2 -1 4 0
 *
 * [출력 예시]
 * -5 -1 0 2 4
 */
#include <stdio.h>
#include <stdlib.h>

// 간단한 배열 기반 LSD 기수 정렬 (큐 없이 구현)
void radixSortSimple(int a[], int n) {
    int maxVal = a[0], minVal = a[0];
    for(int i=1; i<n; i++) {
        if(a[i] > maxVal) maxVal = a[i];
        if(a[i] < minVal) minVal = a[i];
    }
    
    // 오프셋 적용 (모두 양수로)
    int offset = 0;
    if(minVal < 0) offset = -minVal;
    for(int i=0; i<n; i++) a[i] += offset;
    maxVal += offset;

    int exp = 1;
    int* output = (int*)malloc(sizeof(int) * n);
    
    while(maxVal / exp > 0) {
        int count[10] = {0};
        for(int i=0; i<n; i++) count[(a[i]/exp)%10]++;
        for(int i=1; i<10; i++) count[i] += count[i-1];
        for(int i=n-1; i>=0; i--) {
            output[count[(a[i]/exp)%10] - 1] = a[i];
            count[(a[i]/exp)%10]--;
        }
        for(int i=0; i<n; i++) a[i] = output[i];
        exp *= 10;
    }
    
    // 오프셋 복원
    for(int i=0; i<n; i++) a[i] -= offset;
    free(output);
}

int main() {
    int n, a[100];
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", &a[i]);
    radixSortSimple(a, n);
    for(int i=0; i<n; i++) printf("%d ", a[i]);
    return 0;
}