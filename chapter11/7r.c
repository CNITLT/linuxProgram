#include "ch.h"
#include "mymsg.h"
int main(int argc, char **argv, char **env){
	int running = 1, msgid;
	struct my_msg msgbuf;
	long int msg_type = -57;
	if((msgid = msgget((key_t)1234, 0666 | IPC_CREAT)) == -1){
		err_exit("msgget failed\n");
	}
	while(running){
		printf("--------------wait msg-----------\n");
		if(msgrcv(msgid, (void *)&msgbuf, BUFSIZE, msg_type,IPC_NOWAIT) != -1){
			printf("Type Read:%s\n", msgbuf.text);		
		}
		else if(ENOMSG == errno && msgrcv(msgid, (void *)&msgbuf, BUFSIZE,0,0) != -1)
		{
			printf("NoType Read:%s\n", msgbuf.text);		
		}
		else {
			printf("errno = %d\n", errno);
			perror(NULL);
			err_exit("msgrcv failed\n");
		}
		if(strncmp(msgbuf.text,"end",3) == 0){
			break;
		}
	}
	msgctl(msgid, IPC_RMID,0);
	return 0;
}
