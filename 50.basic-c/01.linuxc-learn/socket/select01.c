#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLNE 4096

int main(int argc, char **argv)
{
  int listenfd, connfd, n;
  struct sockaddr_in servaddr;
  char buff[MAXLNE];

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
    return 0;
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(9999);

  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
  {
    printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
    return 0;
  }
  // listen接口之后会一直监听客户端的连接，每次客户端连接，都会和其创建连接（三次连接时内核完成的，不是由应用程序去控制的）
  // 三次握手不发生在任何API中，协议栈本身被动完成的。
  if (listen(listenfd, 10) == -1)
  {
    printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
    return 0;
  }

  // select模型相比于一请求一线程而言
  // 一个select最多支持1024 socket，如果开多个线程，那么是能支持大量socket的。
  // select不能做到100w级别的fd，select函数本身有copy全部监控的socket，循环这些
  // 全部监控的socket存在一定的效率问题

  // fd_set，每个socket对应一个bit位，bit位为1，代表该socket发生了事件。
  // rfds:是需要监控读的集合(从用户copy到内核)
  // rset:是发生了读事件的socket的集合（从内核copy到用户）
  fd_set rfds, rset, wfds, wset;

  FD_ZERO(&rfds);          // 清空bit位
  FD_SET(listenfd, &rfds); // 设置监听的socket的bit位
  FD_ZERO(&wfds);

  // 比如listenfd为100，那么select就需要从第一位bit监控到101位的bit
  int max_fd = listenfd; // select第一个参数为监听socket的最大值+1

  while (1)
  {
    rset = rfds;
    wset = wfds;
    // 一个专门的服务员来给所有的客户端服务，可以知道到底是哪些客户端发生了相应的事件（比如发送了数据给服务器）
    // 如果最后一个参数为NULL，那么是阻塞的，一直到有事件发生（nready会大于0）
    int nready = select(max_fd + 1, &rset, &wset, NULL, NULL);

    if (FD_ISSET(listenfd, &rset))
    { // listenfd监听到了客户端连接

      struct sockaddr_in client;
      socklen_t len = sizeof(client);
      if ((connfd = accept(listenfd, (struct sockaddr *)&client, &len)) == -1)
      {
        printf("accept socket error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
      }

      FD_SET(connfd, &rfds); // 加入到读的集合中，代表要监听某客户端的读（recv）事件

      // 如果客户端没有回收，connfd比max_fd大，但是如果客户端回收了fd，那么数字会变小，因此需要判断当前的connfd是否大于max_fd
      if (connfd > max_fd)
        max_fd = connfd; // 重新设置最大的fd

      if (--nready == 0)
        continue; // 只有一个客户端的连接
    }

    int i = 0;
    // 注意0-标志输入，1-标志输出，2-错误，然后是listenfd，
    // 然后每次客户端连接后，connfd会依次增大。回收后connfd会变小，但是无论如何都比listenfd大
    // 因此这里检测的是所有客户端是否有客户端与服务器进行了通信
    for (i = listenfd + 1; i <= max_fd; i++)
    {

      if (FD_ISSET(i, &rset))
      { // 检测某个客户端是否已经准备好了数据或者关闭（正常关闭也会设置读数据）

        n = recv(i, buff, MAXLNE, 0); //
        if (n > 0)
        { // 收到n个字节的数据
          buff[n] = '\0';
          printf("recv msg from client: %s\n", buff);

          // 设置可以往该客户端socket发送数据
          // 有兴趣的朋友可以去为每个fd封装一个发送缓冲和接收缓冲，设置写标志后
          // 然后再下面的else if (FD_ISSET(i, &wset))发送数据给客户端
          FD_SET(i, &wfds);
          send(i, buff, n, 0); // 直接将接收到的数据发送给客户端
        }
        else if (n == 0)
        {                   // 收到的字节为0，代表该客户端正常关闭了
          FD_CLR(i, &rfds); // 清空该客户端的读事件
          // printf("disconnect\n");
          close(i);
        }
        if (--nready == 0)
          break; // 没有客户端的读事件了
      }
      else if (FD_ISSET(i, &wset))
      { // 某个客户端写事件已就绪
        // send(i, buff, n, 0);  //将前面接收到数据发送给客户端
        // FD_SET(i, &rfds);//
      }
    }
  }
  close(listenfd);
  return 0;
}
