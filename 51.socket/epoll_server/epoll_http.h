#ifndef _EPOLL_SERVER_H
#define _EPOLL_SERVER_H

int init_listen_fd(int port, int epoll_fd);

void epoll_run(int port);

void do_accept(int listen_fd, int epoll_fd);

void do_read(int client_fd, int epoll_fd);

int get_line(int sock, char *buf, int size);

void disconnect(int client_fd, int epoll_fd);

void http_request(const char* request, int client_fd);

void send_respond_head(int client_fd, int no, char *desp, const char* type, long len);

void send_file(int client_fd, const char* filename);

void send_dir(int client_fd, const char* dirname);

void encode_str(char* to, int tosize, const char* from);

void decode_str(char* to, char *from);

const char* get_file_type(const char* name);

#endif
