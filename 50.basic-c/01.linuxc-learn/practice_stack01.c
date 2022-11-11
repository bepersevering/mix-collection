#include <stdio.h>

char stack[512];
int top = 0;

void push(char c) {
  stack[top] = c;
  top++;
}

char pop() {
  top--;
  return stack[top];
}

int isEmpty(void) {
  return top == 0;
}

int main(void) {
  push('a');
  push('b');
  push('c');

  while(!isEmpty()) {
    putchar(pop());
  }
  putchar('\n');

  return 0;
}
