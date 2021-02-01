#include "ch.h"
#include "mymsg.h"
int main(int argc, char **argv, char **env){
	int running = 1, msgid;
	struct my_msg msgbuf;
	struct msqid_ds buf;
	if((msgid = msgget((key_t)1234, 0666 | IPC_CREAT)) == -1){
		err_exit("msgget failed\n");
	}
	while(running){
		printf("Enter text:");
		fgets(msgbuf.text, BUFSIZE, stdin);
		msgbuf.my_msg_type = (long int) msgbuf.text[0];
		memset(msgbuf.text,0,BUFSIZE);
		if(msgsnd(msgid, (void *)&msgbuf, sizeof(struct my_msg),IPC_NOWAIT)== -1){
			err_exit("msgsnd failed\n");
		}
		if(strncmp(msgbuf.text, "end",3) == 0){
			break;
		}
	}
	msgctl(msgid, IPC_RMID,0);
	return 0;
}
