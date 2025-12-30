#include <stdio.h>

int main(void) {

    int i = 100; 
    int *p = (int *)100;

    printf("i = %d\n", i);
    printf("p = %p\n", p);
    printf("*p = %d\n", *p);
    printf("(int)p + 1 = %d\n", *((int *)p + 1));
    printf("(int)(p + 1) = %d\n", (*(int *)(p + 1)));

  
    return 0;
}
