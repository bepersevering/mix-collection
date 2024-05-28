#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// 信号处理
void timeout(int sig) {
   if (sig == SIGALRM) {
    puts("Time out!");
  }
  // 为了每隔2秒重复产生 SIGALRM 信号，在信号处理器中调用alarm函数
  alarm(2);
}

// 信号处理器
void keycontrol(int sig) {
  if (sig == SIGINT) {
    puts("CRL + c pressed");
  }
}

int main(int argc, char **argv) {
  int i;

  signal(SIGALRM, timeout); // 注册信号及相应处理器
  signal(SIGINT, keycontrol);

  alarm(2); // 预约2秒后发生 SIGALRM 信号

  for (i = 0; i < 3; i++) {
    puts("wait...");
    sleep(100);
  }

  return 0;
}
