#include "mysocket.h"
int make_un_socket(int type, const char *filename){
	struct sockaddr_un name;
	int sock;
	socklen_t size;
	sock = socket(AF_UNIX, type, 0);
	if(sock < 0){
		err_exit("socket");
	}
	name.sun_family = AF_UNIX;
	strcpy(name.sun_path, filename);
	size = sizeof(struct sockaddr_un) + 1;
	if(bind(sock, (struct sockaddr_un *)&name,size)<0){
		err_exit("bind failed\n");
	}
	return sock;
}
void init_sockaddr(struct sockaddr_in *name, const char *hostname, const char *serv){
	struct hostent *hp;
	char *host, myname[255];
	if(!hostname){
			gethostname(myname,sizeof(myname));
			host = myname;
	}
	else{
		host = hostname;
	}
	if(NULL == (hp = gethostbyname(host))){
		err_exit("init_sockaddr gethostbyname failed\n");
	}
	bzero(name,sizeof(struct sockaddr_in));
	if(hp->h_addrtype == AF_INET){
		name->sin_family = AF_INET;
		bcopy(hp->h_addr_list[0], &name->sin_addr, hp->h_length);
		if(NULL == serv){
			name->sin_port = htons(0);
		}
		else{
			name->sin_port = htons(atoi(serv));
		}
	}
	else{
		err_exit("Unknown address type\n");
	}
}
int make_socket(int type, unsigned short int port){
		int sock;
		struct sockaddr_in name;
		if((sock = socket(AF_INET,type,0)) < 0){
			err_exit("socket");
		}
		name.sin_family = AF_INET;
		name.sin_port = htons(port);
		name.sin_addr.s_addr = htonl(INADDR_ANY);
		if(bind(sock,(struct sockaddr *)&name, (socklen_t)sizeof(name)) < 0){
		err_exit("bind");
		}
		return sock;
}


int socket_connect(char *hostname, char *serv_port){
	int sockfd;
	struct sockaddr_in saddr;
	struct hostent *hp;
	char *host, myname[104];
	init_sockaddr(&saddr, hostname, serv_port);
	if((sockfd = socket(AF_INET, SOCK_STREAM,0))<0){
			err_exit("socket_connect socket failed\n");
	}

	if(connect(sockfd, (struct sockaddr*)&saddr, sizeof(saddr))<0){
			err_exit("socket_connect connect failed\n");
	}
	return sockfd;
}

