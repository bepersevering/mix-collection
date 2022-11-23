#include <stdio.h>

int main(void) {

	char s[] = "hello";
	char * const s1 = "hello";

	char x = 'A';

	char *p1 = &x;

	char const *p2 = &x;
	const char *p3 = &x;


	*p2 = 'B';
	*p3 = 'C';

	*p1 = 'm';

	char str[]  = "Hello worlld";
	char *const p = str;

	p = &str[1];

	printf("%s\n", p);


	printf("s = %s \n", s);
	printf("s1 = %s \n", s1);

	return 0;
}
