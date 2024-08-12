#ifndef _SELECT_SERVER_H
#define _SELECT_SERVER_H

int init_listen_fd(int port);

void select_run(int port);

void do_accept(int listen_fd);

void do_read(int client_fd);

int get_line(int sock_fd, char *buf, int size);

void disconnect(int client_fd);

void http_request(const char* request, int client_fd);

void send_respond_head(int client_fd, int status, char *desp, char *type, long len);

void send_file(int client_fd, const char* filename);

void send_dir(int client_fd, const char* dirname);

void encode_str(char* to, int tosize, const char* from);

void decode_str(char* to, char* from);

const char* get_file_type(const char* name);


#endif
