// unp header

#ifndef __unp_h
#define __unp_h

#include <apra/inet.h>
#include <netinet/in.h> /* sockaddr_in{} and other internet defns */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

/* Miscellaneous constants */
#define MAXLINE 4096 /* max text line length */

void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);

#endif /* __unp_h */
