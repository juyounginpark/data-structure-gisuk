/*
 * [변형 문제 2] Quick Sort with Median-of-Three Pivot
 *
 * [문제 설명]
 * 퀵 정렬의 성능 향상을 위해 피벗을 (맨 앞, 중간, 맨 뒤) 요소의 중간값으로 선택하여 정렬하시오.
 *
 * [입력 예시]
 * 5
 * 5 2 4 1 3
 *
 * [출력 예시]
 * 1 2 3 4 5
 */

#include <stdio.h>
#define SWAP(x, y, t) { t = x; x = y; y = t; }

int getMedianIndex(int a[], int left, int right) {
    int mid = (left + right) / 2;
    // 세 값(left, mid, right) 중 중간값을 가지는 인덱스 반환
    if (a[left] > a[mid]) SWAP(a[left], a[mid], mid); // 임시 변수로 mid 활용(타입 주의, 여기선 단순 예시)
    if (a[mid] > a[right]) SWAP(a[mid], a[right], mid);
    if (a[left] > a[mid]) SWAP(a[left], a[mid], mid);
    return mid; // 정렬 후 중간값은 mid 위치에 옴
}

void quickSortMedian(int a[], int left, int right) {
    if (left >= right) return;

    // Median-of-three 전략: 중간값을 찾아 맨 앞으로 보냄 (기존 로직 활용 위해)
    int mid = (left+right)/2;
    int temp;
    // 간단히 left, mid, right 정렬하여 mid를 pivot 후보로 만듦
    if (a[left] > a[mid]) SWAP(a[left], a[mid], temp);
    if (a[mid] > a[right]) SWAP(a[mid], a[right], temp);
    if (a[left] > a[mid]) SWAP(a[left], a[mid], temp);
    
    // a[mid]가 중간값이므로 이를 left+1 위치(혹은 left)로 옮겨서 피벗으로 사용
    // 여기서는 편의상 a[mid]를 a[left]와 교환하여 기존 파티션 로직 사용
    SWAP(a[left], a[mid], temp);
    
    int pivot = a[left];
    int i = left, j = right + 1;

    do {
        do { i++; } while (i <= right && a[i] < pivot);
        do { j--; } while (j > left && a[j] > pivot);
        if (i < j) SWAP(a[i], a[j], temp);
    } while (i < j);

    SWAP(a[left], a[j], temp);
    quickSortMedian(a, left, j - 1);
    quickSortMedian(a, j + 1, right);
}

int main() {
    int n, a[100];
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%d", &a[i]);
    quickSortMedian(a, 1, n);
    for(int i=1; i<=n; i++) printf("%d ", a[i]);
    return 0;
}