#include <unistd.h>

char msg[14] = "Hello World!\n";
#define len 14

int main(void) {
  write(1, msg, len);
  _exit(0);
}
