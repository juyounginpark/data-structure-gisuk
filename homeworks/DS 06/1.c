/*2025002720 박주영
본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1

typedef struct{
	char name[20];
	int age;
	float salary;

} humanBeing;

int humansEqual ( humanBeing *person1, humanBeing *person2 )
{
	if(strcmp(person1->name, person2->name))
		return FALSE;
	
	if( person1->age != person2->age)
		return FALSE;

	if( person1->salary != person2->salary )
		return FALSE;

	return TRUE;
}


int main() {
	humanBeing human[2];

	printf("Input person1's name, age, salary :\n");
	fgets(human[0].name, sizeof(human[0].name), stdin);
	scanf("%d %f", &human[0].age, &human[0].salary);

	printf("Input person2's name, age, salary :\n");
	scanf("\n");
	fgets(human[1].name, sizeof(human[1].name), stdin);
	scanf("%d %f", &human[1].age, &human[1].salary);

	
	if(humansEqual(&human[0], &human[1])) {
		printf("=> The two human beings are the same\n");
	}
	else {
		printf("=> The two human beings are not the same\n");
	}
	


}	
