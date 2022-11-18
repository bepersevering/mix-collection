char stack[512];

int top = -1;

void push(char c) {
  stack[++top] = c;
}

char pop() {
  return stack[top--];
}

int isEmpty(void) {
  return top == -1;
}
