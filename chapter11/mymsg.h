
#ifndef _MYMSG_H
#define _MYMSG_H
#ifndef BUFSIZE
#define BUFSIZE 1024
#endif
struct my_msg{
	long int my_msg_type;
	char text[BUFSIZE];
};
#endif
