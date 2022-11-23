#include <stdio.h>

int main(void) {
	const char wang[] = {"wang"};

	char *p;

	p = wang;
	p[2] = 'c';

	printf("p is %s\n", p);

	return 0;
}
