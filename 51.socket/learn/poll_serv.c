#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <poll.h>

/* 定义socket可排队个数 */
#define BACKLOG			10
/* 此宏用来计算数组的元素个数 */
#define ARRAY_SIZE(x) 	(sizeof(x)/sizeof(x[0]))

int socket_server_init(char *listen_ip, int listen_port);

int main(int argc, char **argv)
{
	int listen_fd = -1; 
	int client_fd = -1;
	int rv = -1;
	int listen_port = 0;
	int max = 0;
	struct pollfd fds_array[1024];
	int i, j;
	int found;
	char buf[1024];
	

	/* 用来确认程序执行的格式是否正确，不正确则退出并提醒用户 */
	if (argc < 2)
	{
		printf("Program usage: %s [Port]\n", argv[0]);
		return -1;
	}
	
	//将端口参数赋给参数变量
	//由于命令行传参进来是字符串类型，所以需要atoi转换为整型
	listen_port = atoi(argv[1]);
	
	/* 创建listen_fd，这里封装了一个函数 */
	if ((listen_fd = socket_server_init(NULL, listen_port)) < 0)
	{
		printf("server listen on port[%d] failure: %s\n", listen_port, strerror(errno));
		return -2;
	}
	
	/* 将数组中每个元素都设置为-1，相当于清空fd */
	for (i=0; i<ARRAY_SIZE(fds_array); i++)
	{
		fds_array[i].fd = -1;
	}
	/* 将listen_fd和期待POLLIN存入结构体数组第0个元素中 */
	fds_array[0].fd = listen_fd;
	fds_array[0].events = POLLIN;
	
	/* 当前结构体中，最大的下标是0 */
	max = 0;

	while (1)
	{
		/*
		 * poll遍历结构体数组，个数为max+1，永不超时
		 * 返回结构体中 revents 域不为0的文件描述符个数；
		 * 返回0：说明在超时前没有任何事件发生；
		 * 返回-1：说明失败
		 */
		if ((rv = poll(fds_array, max+1, -1)) < 0)
		{
			printf("poll failure: %s\n", strerror(errno));
			break;
		}
		else if (rv == 0)
		{
			printf("poll timeout\n");
			continue;
		}

		/* 有消息来了 */
		/* 判断是不是listen_fd的消息 */
		if (fds_array[0].revents & POLLIN)
		{
			/*
			 * accept()
			 * 接受来自客户端的连接请求
			 * 返回一个client_fd与客户通信
			 */
			if ((client_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL)) < 0)
			{
				printf("accept new client failure: %s\n", strerror(errno));
				continue;
			}
			
			/*
			 * 在把client_fd放到数组中的空位中
			 * （元素的值为-1的地方）
			 */
			found = 0;
			for (i=0; i<ARRAY_SIZE(fds_array); i++)
			{
				if (fds_array[i].fd < 0)
				{
					printf("accept new client[%d] and add it to array\n", client_fd);
					fds_array[i].fd = client_fd;
					fds_array[i].events = POLLIN;
					found = 1;
					/* 更新结构体数组中的当前最大下标 */
					max = i>max ? i : max;
					break;
				}
			}
			
			/*
			 * 如果没找到空位，表示数组满了
			 * 不接收这个新客户端，关掉client_fd
			 */
			if (!found)
			{
				printf("accept new client[%d] but full, so refuse\n", client_fd);
				close(client_fd);
			}		

		}
		else	/* 来自已连接客户端的消息 */
		{
			for (i=0; i<ARRAY_SIZE(fds_array); i++)
			{
				/* 判断fd是否有效，并且查看当前fd实际发生的事件是不是POLLIN */
				if (fds_array[i].fd<0 || !(fds_array[i].revents & POLLIN))
					continue;
				
				/* 清空buf，以便存放读取的数据 */
				memset(buf, 0, sizeof(buf));
				if ((rv = read(fds_array[i].fd, buf, sizeof(buf))) <= 0)
				{
					printf("client[%d] read failure or get disconnect\n", fds_array[i].fd);
					close(fds_array[i].fd);
					fds_array[i].fd = -1;
					if (i == max)
						max--;
					continue;
				}
				printf("read %d Bytes data from client[%d]: %s\n", rv, fds_array[i].fd, buf);
				
				/* 将小写字母转为大写 */
				for (j=0; j<rv; j++)
				{
					if (buf[j] >= 'a' && buf[j] <= 'z')
						buf[j] = toupper(buf[j]);
				}
				
				/* 将数据发送到客户端 */
				if ((rv = write(fds_array[i].fd, buf, rv)) < 0)
				{
					printf("write data to client[%d] failure: %s\n", client_fd, strerror(errno));
					close(fds_array[i].fd);
					fds_array[i].fd = -1;
					if (i == max)
						max--;
					continue;
				}
				printf("write %d Bytes data to client[%d]: %s\n\n", rv, fds_array[i].fd, buf);
			} /* end of for() */

		} /* cliet_fd message */

	} /* while(1) */
	
	close(listen_fd);
	return 0;

} /* end of main() function */

/*
 * Socket Server Init Function
 * 创建 listen_fd，bind绑定ip和端口，并监听
 */
int socket_server_init(char *listen_ip, int listen_port)
{	
	int					rv = 0;
	int					listen_fd = -1;
	struct sockaddr_in	servaddr;
	int					on = 1;
	
	/*
	 * socket()，创建一个新的sockfd
	 * 指定协议族为IPv4
	 * socket类型为SOCK_STREAM（TCP）
	 */
	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{		
		printf("create listen_fd failure: %s\n", strerror(errno));
		return -1;
	}
	printf("create listen_fd[%d] success\n", listen_fd);

	//设置套接字端口可重用，修复了当Socket服务器重启时“地址已在使用(Address already in use)”的错误
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	/*
	 * bind()，将服务器的协议地址绑定到listen_fd
	 */
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(listen_port);
	if (!listen_ip)	//如果ip为空，则监听本机所有ip
	{
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		/* 将点分十进制的ip地址转为32位整型传入结构体 */
		if (inet_pton(AF_INET, listen_ip, &servaddr.sin_addr) <= 0)
		{
			printf("inet_pton set listen_ip address failure: %s\n", strerror(errno));
			rv = -2;
			goto cleanup;
		}
	}

	if (bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("bind listen_fd[%d] failure: %s\n", listen_fd, strerror(errno));
		rv = -3;
		goto cleanup;
	}

	/*
	 * listen()
	 * 监听listen_fd的端口，并设置最大排队连接个数
	 */
	if (listen(listen_fd, BACKLOG) < 0)
	{
		printf("listen listen_fd on listen_port[%d] failure: %s\n", listen_port, strerror(errno));
		rv = -4;
		goto cleanup;
	}

cleanup:
	if (rv < 0)
		close(listen_fd);
	else
		rv = listen_fd;

	return rv;
}

