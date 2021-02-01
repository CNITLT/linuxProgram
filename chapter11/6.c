#include "ch.h"
void show_msq_stat(struct msqid_ds *buf);
int main(int argc, char **argv, char **env){
	key_t key;
	int new, msqid, msgflg;	
	struct msqid_ds buf;
	printf("Enter the disired key = ");
	scanf("%d",&key);
	msgflg = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	if((msqid = msgget(key, msgflg | IPC_CREAT | IPC_EXCL)) > 0){
		new = 1;
	}
	else if(EEXIST == errno){
		new = 0;
		msqid = msgget(key,msgflg);
	}
	else{
		err_exit("The msgget failed\n");
	}
	if(-1 == msgctl(msqid, IPC_STAT, &buf)){
		err_exit("msgctl failed\n");
	}
	show_msq_stat(&buf);
	if(new){
		msgctl(msqid,IPC_RMID,NULL);
	}
	return 0;
}
void show_msq_stat(struct msqid_ds *buf){
printf("The USER ID = %d\n",buf->msg_perm.uid);
printf("The GROUP ID = %d\n",buf->msg_perm.gid);
printf("The CReATOR ID = %d\n",buf->msg_perm.cuid);
printf("The CREADTOR's GROUP ID = %d\n",buf->msg_perm.cgid);
printf("The operation permissions = %#o\n",buf->msg_perm.mode);
printf("access permissions = %#o\n",buf->msg_perm.mode & 0777);
printf("msg_cbytes = %ld\n",buf->msg_cbytes);
printf("msg_qbytes = %ld\n",buf->msg_qbytes);
printf("msg_qnum = %ld\n",buf->msg_qnum);
printf("msg_lspid = %d\n",buf->msg_lspid);
printf("msg_lrpid = %d\n",buf->msg_lrpid);
printf("msg_stime = %s",buf->msg_stime ? (char *)ctime(&(buf->msg_stime)):"Not Set\n");
printf("msg_rtime = %s",buf->msg_rtime ? (char *)ctime(&(buf->msg_rtime)):"Not Set\n");
printf("msg_cime = %s",ctime(&(buf->msg_ctime)));
}
