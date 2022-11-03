#include <stdio.h>

int factorial(int n) {
	if (n == 0) {
		return 1;
	}
	else {
		int recurse = factorial(n - 1);
		int result = n * recurse;
		return result;
	}
}

int main(void) {
	int n = 10;

	int factorial_n = factorial(n);

	printf("n! = %d\n", factorial_n);

	return 0;
}
