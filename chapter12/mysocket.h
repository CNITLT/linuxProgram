#ifndef _MY_SOCKET_H
#define _MY_SOCKET_H
#include "ch.h"
int make_un_socket(int type, const char *filename);
void init_sockaddr(struct sockaddr_in *name, const char *hostname, const char *serv);
int make_socket(int type, unsigned short int port);
int socket_connect(char *hostname, char *serv_port);
#endif
