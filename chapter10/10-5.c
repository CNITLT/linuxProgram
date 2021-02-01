#include "ch.h"
void input_ready(int signo);
void sigusr1(int signo);
void stack_w();
FILE *file;
int main(int argc, char **argv, char **env){
	printf("pid:%d\n",getpid());
	if(signal(SIGUSR1,sigusr1) < 0){
		perror(NULL);
		err_exit("signal SIGUSR1 failed\n");
	}
	int flags;
	char buffer[64];
	struct termios newsettings, oldsettings;
	file = fopen("tesfile", "w");
	int in = open("tesIn", O_RDONLY | O_CREAT | O_NONBLOCK | O_ASYNC, 0644);
	dup2(in,STDIN_FILENO);
	signal(SIGIO,input_ready);
	/*
	tcgetattr(STDIN_FILENO, &oldsettings);
	newsettings = oldsettings;
	newsettings.c_lflag &= (~ICANON);
	newsettings.c_cc[VTIME] = 0;
	newsettings.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &newsettings);
	*/

	fcntl(STDIN_FILENO, F_SETOWN, getpid());
	flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	flags |= O_ASYNC | O_NONBLOCK;
	fcntl(STDIN_FILENO,F_SETFL,flags);
	stack_w();
	while(1) {
		sleep(30);
		printf("\n\n-----------------------\n\n");
		printf("main\n");
		stack_w();
		printf("\n\n-----------------------\n\n");
	}
	return 0;
}
void stack_w(){
	char buf[1024 * 1024];
	memset(buf,'a',sizeof(buf));
	printf("stack_w stack addr start:#%x, end:#%x\n",buf,buf+sizeof(buf));
}

void input_ready(int signo){
	printf("\n\n-----------------------\n\n");
	printf("sig:SIGIO sig:%d function start\n",signo);
	char c,input[80];
	printf("input addr start:#%x end:#%x\n",input,input + 80);
	int n;
	static int i = 0;
	if(read(STDIN_FILENO, &c, 1) > 0)
	{
		
		if('\n' != c){
			input[i++] = c;
			printf("\ninput buf:%s read char:%c\n",input,c);

		}
		else{
			input[i++] = '\0';
			fprintf(file, "received %d SIGIOs, and Input line is :%s\n", i, input);
			i = 0;
			memset(input,0,sizeof(input));
		}
		if('q' == input[0]){
			fclose(file);
			exit(0);
		}
	}

	printf("sig:SIGIO sig:%d function end\n",signo);
	printf("\n\n-----------------------\n\n");
} 

void sigusr1(int signo){
	printf("\n\n-----------------------\n\n");
	int a;
	printf("sigusr1 stack :#%x\n", &a);
	stack_w();
	printf("\n\n-----------------------\n\n");
}
