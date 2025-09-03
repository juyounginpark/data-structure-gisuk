#include <stdio.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
	return;
}

int main() {
	int a, b;
	int t;
	a = 1;
	b = 2;
	swap(&a, &b);
	SWAP(a, b, t);
	printf("%d %d", a, b);
	return 0;

}
