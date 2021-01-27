#include "ch.h"
#define TTY_OUTPUT 1
static struct termios old_term, new_term;
void do_exit(int);
void set_tty(){
	new_term.c_iflag &= ~(ICRNL | IGNCR | INLCR | BRKINT);
	new_term.c_oflag &= ~ OPOST;
	new_term.c_lflag |= ISIG | NOFLSH;
	new_term.c_lflag &= ~(ICANON);
	new_term.c_cc[VINTR]= 7;
	
	new_term.c_cc[VQUIT]= 8;
	new_term.c_cc[VMIN]= 1;
	new_term.c_cc[VTIME]= 0;
	tcsetattr(TTY_OUTPUT, TCSADRAIN, &new_term);
}
void tty_init(){
	tcgetattr(TTY_OUTPUT,&old_term);
	new_term = old_term;
	signal(SIGTERM, do_exit);
	signal(SIGQUIT, do_exit);
	signal(SIGINT, do_exit);
	set_tty();
}
void tty_end(){
	tcsetattr(TTY_OUTPUT, TCSADRAIN, &old_term);
}
void do_exit(int signum)
{
	tty_end();
	exit(1);
}
int main(int argc, char **argv, char **env){
	char c;
	printf("Display key sequence utility\n");
	printf("Press space when done\n\n");
	tty_init();
	while(1){
		read(0,&c,1);
		if(' ' == c){
			break;
		}	
		printf("%x\n",c);
		fflush(stdout);
	
	}
	tty_end();

	return 0;
}
