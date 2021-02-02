#include "showHostent.h"
void showHostent(const struct hostent* hostPtr){
	printf("-------------------------------------------------\n");
	printf("h_name:%s\n",hostPtr->h_name);
	char **p = hostPtr->h_aliases;
	if(!(*p)){
		printf("no h_aliases");
	}
	else{
		int i = 0;
		for(;*p;i++,p++){
			printf("h_aliases[%d]:%s\n",i,*p);
		}
	}
	printf("h_addrtype:%s\n", 
		hostPtr->h_addrtype == AF_INET?"AF_INET":
		(hostPtr->h_addrtype == AF_INET6?"AF_INET6":"Unknowed"));
	printf("h_length:%d\n",hostPtr->h_length);
	p = hostPtr->h_addr_list;
	if(!(*p)){
		printf("no h_addr_list");
	}
	else{
		char buf[INET6_ADDRSTRLEN];
		int i = 0;
		for(;*p;i++,p++){
			printf("h_addr[%d]:%s\n",i,
			inet_ntop(hostPtr->h_addrtype,(void *)*p,buf,INET6_ADDRSTRLEN));
		}
	
	}
	printf("-------------------------------------------------\n");
}
