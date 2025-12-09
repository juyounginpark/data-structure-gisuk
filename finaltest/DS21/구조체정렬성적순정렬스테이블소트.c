/*
 * [변형 문제 5] Stable Sort by Grade
 *
 * [문제 설명]
 * 학생 이름과 점수를 입력받아 점수 내림차순으로 정렬하시오.
 * 합병 정렬을 사용하여 안정 정렬(Stable Sort)임을 확인하시오.
 *
 * [입력 예시]
 * 3
 * Lee 80
 * Kim 100
 * Park 80
 *
 * [출력 예시]
 * Kim 100
 * Lee 80    (Lee가 Park보다 먼저 입력되었으므로 먼저 출력됨)
 * Park 80
 */

#include <stdio.h>
#define MAX_SIZE 100

typedef struct {
    char name[20];
    int grade;
} Student;

Student sorted[MAX_SIZE];

void mergeStudents(Student list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        // 점수가 같으면 왼쪽(먼저 입력된 것)을 먼저 선택하여 안정성 유지
        if (list[i].grade >= list[j].grade) sorted[k++] = list[i++];
        else sorted[k++] = list[j++];
    }
    while (i <= mid) sorted[k++] = list[i++];
    while (j <= right) sorted[k++] = list[j++];
    for (int l = left; l <= right; l++) list[l] = sorted[l];
}

void mergeSortStudents(Student list[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortStudents(list, left, mid);
        mergeSortStudents(list, mid + 1, right);
        mergeStudents(list, left, mid, right);
    }
}

int main() {
    int n;
    Student list[MAX_SIZE];
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%s %d", list[i].name, &list[i].grade);

    mergeSortStudents(list, 0, n - 1);

    for(int i=0; i<n; i++) printf("%s %d\n", list[i].name, list[i].grade);
    return 0;
}