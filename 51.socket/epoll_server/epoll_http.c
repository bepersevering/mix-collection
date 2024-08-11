#include "epoll_http.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SIZE 2000

void epoll_run(int port) {
  // 创建一个epoll树的根节点
  int epoll_fd = epoll_create(MAX_SIZE);
  if (-1 == epoll_fd) {
    perror("epoll_create error");
    exit(1);
  }

  // 添加要监听的节点
  // 先添加监听listen_fd
  int listen_fd = init_listen_fd(port, epoll_fd);
  // 委托内核检测添加到树上的节点
  struct epoll_event all_events[MAX_SIZE];

  while (1) {
    int ret = epoll_wait(epoll_fd, all_events, MAX_SIZE, 0);
    if (-1 == ret) {
      perror("epoll_wait error");
      exit(1);
    }

    // 遍历发生变化的节点
    int i = 0;
    for (i = 0; i < ret; ++i) {
      // 只处理读事件，其他事件默认不处理
      struct epoll_event *pev = &all_events[i];
      if (!(pev->events & EPOLLIN)) {
        // 不是读事件
        continue;
      }

      if (pev->data.fd == listen_fd) {
        // 接受连接请求
        do_accept(listen_fd, epoll_fd);
      } else {
        // 读数据
        do_read(pev->data.fd, epoll_fd);
      }
    }
  }
}

/**
 * 读数据
 */
void do_read(int client_fd, int epoll_fd) {
  // 将浏览器发过来的数据，读到buf中
  char line[1024] = {0};
  // 读请求行
  int len = get_line(client_fd, line, sizeof(line));

  if (0 == len) {
    printf("client disconnect...\n");
    // 关闭套接字，client_fd从epoll上del
    disconnect(client_fd, epoll_fd);
  } else {
    printf("request data: %s", line);
    printf("============= request header ============\n");
    // 还有数据没读完
    // 继续读
    while (len) {
      char buf[1024] = {0};
      len = get_line(client_fd, buf, sizeof(buf));
      printf("-----: %s", buf);
    }
    printf("============= The End ============\n");
  }

  // 请求行：get /xxx http/1.1
  // 判断是汪是get请求
  if (strncasecmp("get", line, 3) == 0) {
    // 处理http请求
    http_request(line, client_fd);
    // 关闭套接字，client_fd从epoll上del
    disconnect(client_fd, epoll_fd);
  }
}

// 断开连接的函数
void disconnect(int client_fd, int epoll_fd) {
  int ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
  if (ret == -1) {
    perror("epoll_ctl_del cfd erro");
    exit(1);
  }
  close(client_fd);
}

// 处理http请求
void http_request(const char *request, int client_fd) {
  // 拆分http请求行
  // get /xxx http/1.1
  char method[12], path[1024], protocol[12];
  sscanf(request, "%[^ ] %[^ ] %[^ ]", method, path, protocol);

  printf("method = %s, path = %s, protocol = %s\n", method, path, protocol);

  // 转码 将不能识别的中文乱码 - > 中文
  // 解码 %23 %34 %5f
  decode_str(path, path);
  // 处理path  /xx
  // 去掉path中的/
  char *file = path + 1;
  // 如果没有指定访问的资源, 默认显示资源目录中的内容
  if (strcmp(path, "/") == 0) {
    // file的值, 资源目录的当前位置
    file = "./";
  }

  // 获取文件属性
  struct stat st;
  int ret = stat(file, &st);
  if (ret == -1) {
    // show 404
    send_respond_head(client_fd, 404, "File Not Found", ".html", -1);
    send_file(client_fd, "404.html");
  }

  // 判断是目录还是文件
  // 如果是目录
  if (S_ISDIR(st.st_mode)) {
    // 发送头信息
    send_respond_head(client_fd, 200, "OK", get_file_type(".html"), -1);
    // 发送目录信息
    send_dir(client_fd, file);
  } else if (S_ISREG(st.st_mode)) {
    // 文件
    // 发送消息报头
    send_respond_head(client_fd, 200, "OK", get_file_type(file), st.st_size);
    // 发送文件内容
    send_file(client_fd, file);
  }
}

// 发送目录内容
void send_dir1(int client_fd, const char *path) {}

// 发送目录内容
void send_dir(int client_fd, const char *dirname) {
  char file[1024] = {0};
  char buf[4096] = {0};
  sprintf(buf, "<html><head><title>目录名: %s</title></head>", dirname);
  sprintf(buf + strlen(buf), "<body><h1>当前目录: %s</h1><table>", dirname);
#if 1
  DIR *dir = opendir(dirname);
  if (dir == NULL) {
    perror("opendir error");
    exit(1);
  }
  // 读目录
  char enstr[1024] = {0};
  struct dirent *ptr = NULL;
  while ((ptr = readdir(dir)) != NULL) {
    char *name = ptr->d_name;
    // 拼接文件的完整路径
    sprintf(file, "%s/%s", dirname, name);

    encode_str(enstr, sizeof(enstr), name);
    struct stat st;
    int ret = stat(file, &st);
    if (ret == -1) {
      perror("stat err");
      exit(1);
    }
    // 如果是文件
    if (S_ISREG(st.st_mode)) {
      sprintf(buf + strlen(buf),
              "<tr><td><a href=\"%s\">%s</a></td><td>%ld</td></tr>", enstr,
              name, (long)st.st_size);
    }
    // 如果是目录
    else if (S_ISDIR(st.st_mode)) {
      sprintf(buf + strlen(buf),
              "<tr><td><a href=\"%s/\">%s/</a></td><td>%ld</td></tr>", enstr,
              name, (long)st.st_size);
    }
    send(client_fd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));
  }
  sprintf(buf + strlen(buf), "</table></body></html>");
  send(client_fd, buf, strlen(buf), 0);
#endif
}

// 发送响应头
void send_respond_head(int client_fd, int status, char *desp, const char *type,
                       long len) {
  char buf[1024] = {0};
  // 状态行
  sprintf(buf, "http/1.1 %d %s\r\n", status, desp);
  send(client_fd, buf, strlen(buf), 0);
  // 消息报头
  memset(buf, 0, sizeof buf);
  sprintf(buf, "Content-Type:%s\r\n", type);
  sprintf(buf + strlen(buf), "Content-Length:%ld\r\n", len);
  send(client_fd, buf, strlen(buf), 0);
  // 空行
  send(client_fd, "\r\n", 2, 0);
}

// 发送文件
void send_file(int client_fd, const char *filename) {
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    // todo 404
    perror("open err");
    exit(1);
  }

  char buf[4096];
  int ret = 0;
  while ((ret = read(fd, buf, sizeof buf)) > 0) {
    send(client_fd, buf, ret, 0);
  }
  if (ret == -1) {
    perror("read err");
    exit(1);
  }
  close(fd);
}

// 解析hhtp请求消息的每一行内容
int get_line(int sock, char *buf, int size) {
  int i = 0;
  char c = '\0';
  int n;

  while ((i < size - 1) && (c != '\n')) {
    // 接收1个字节
    n = recv(sock, &c, 1, 0);
    if (n > 0) {
      if (c == '\r') {
        n = recv(sock, &c, 1, MSG_PEEK);
        if ((n > 0) && (c == '\n')) {
          recv(sock, &c, 1, 0);
        } else {
          c = '\n';
        }
      }
      buf[i] = c;
      i++;
    } else {
      c = '\n';
    }
  }

  buf[i] = '\0';

  return i;
}

// 接受新连接处理
void do_accept(int listen_fd, int epoll_fd) {
  struct sockaddr_in client_addr;

  socklen_t client_len = sizeof(client_addr);

  int client_fd =
      accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);

  if (client_fd == -1) {
    perror("accept error");
    exit(1);
  }

  // 打印客户端信息
  char ip[64] = {0};

  printf("New Client IP: %s, Port: %d, client_fd = %d\n",
         inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip, sizeof(ip)),
         ntohs(client_addr.sin_port), client_fd);

  // 设置client_fd为非阻塞
  int flag = fcntl(client_fd, F_GETFL);
  flag |= O_NONBLOCK;
  fcntl(client_fd, F_SETFL, flag);

  // 得到新的节点持到epoll树上
  struct epoll_event ev;
  ev.data.fd = client_fd;
  // 边沿非阻塞模式
  ev.events = EPOLLIN | EPOLLET;
  int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev);
  if (ret == -1) {
    perror("epoll_ctl add client_fd erro");
    exit(1);
  }
}

int init_listen_fd(int port, int epoll_fd) {

  // 创建监听的套接字
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd == -1) {
    perror("create socket error");
    exit(1);
  }

  // listen_fd 绑定本地IP和port
  struct sockaddr_in serv_addr;
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // 端口复用
  int flag = 1;
  setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

  int ret = bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

  if (ret == -1) {
    perror("bind error");
    exit(1);
  }

  // 设置监听
  ret = listen(listen_fd, 64);
  if (ret == -1) {
    perror("listen error");
    exit(1);
  }

  // listen_fd 添加到epoll树上
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = listen_fd;

  ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);
  if (ret == -1) {
    perror("epoll_ctl add listen_fd error");
    exit(1);
  }

  return listen_fd;
}

// 16进制数转化为10进制
int hexit(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;

  return 0;
}

/*
 *  这里的内容是处理%20之类的东西！是"解码"过程。
 *  %20 URL编码中的‘ ’(space)
 *  %21 '!' %22 '"' %23 '#' %24 '$'
 *  %25 '%' %26 '&' %27 ''' %28 '('......
 *  相关知识html中的‘ ’(space)是&nbsp
 */
void encode_str(char *to, int tosize, const char *from) {
  int tolen;

  for (tolen = 0; *from != '\0' && tolen + 4 < tosize; ++from) {
    if (isalnum(*from) || strchr("/_.-~", *from) != (char *)0) {
      *to = *from;
      ++to;
      ++tolen;
    } else {
      sprintf(to, "%%%02x", (int)*from & 0xff);
      to += 3;
      tolen += 3;
    }
  }
  *to = '\0';
}

void decode_str(char *to, char *from) {
  for (; *from != '\0'; ++to, ++from) {
    if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2])) {
      *to = hexit(from[1]) * 16 + hexit(from[2]);
      from += 2;
    } else {
      *to = *from;
    }
  }
  *to = '\0';
}

// 通过文件名获取文件的类型
const char *get_file_type(const char *name) {
  char *dot;
  // 自右向左查找‘.’字符, 如不存在返回NULL
  dot = strrchr(name, '.');
  if (dot == NULL)
    return "text/plain; charset=utf-8";
  if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
    return "text/html; charset=utf-8";
  if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
    return "image/jpeg";
  if (strcmp(dot, ".gif") == 0)
    return "image/gif";
  if (strcmp(dot, ".png") == 0)
    return "image/png";
  if (strcmp(dot, ".css") == 0)
    return "text/css";
  if (strcmp(dot, ".au") == 0)
    return "audio/basic";
  if (strcmp(dot, ".wav") == 0)
    return "audio/wav";
  if (strcmp(dot, ".avi") == 0)
    return "video/x-msvideo";
  if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
    return "video/quicktime";
  if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
    return "video/mpeg";
  if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
    return "model/vrml";
  if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
    return "audio/midi";
  if (strcmp(dot, ".mp3") == 0)
    return "audio/mpeg";
  if (strcmp(dot, ".ogg") == 0)
    return "application/ogg";
  if (strcmp(dot, ".pac") == 0)
    return "application/x-ns-proxy-autoconfig";

  return "text/plain; charset=utf-8";
}
