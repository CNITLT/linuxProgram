#include "ch.h"
struct termios saved_attributes;
void resume_input_mode(void){
	tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);

}
void set_input_mode(int fd){
	struct termios tattr;
	char *name;
	if(!isatty(fd)){
		err_exit("Not a terminal\n");
	}
	tcgetattr(fd, &saved_attributes);
	tcgetattr(fd, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO,TCSAFLUSH, &tattr);
}
int main(int argc, char **argv, char **env){
	char c;
	set_input_mode(STDIN_FILENO);	
	while(1){
		read(STDIN_FILENO,&c,1);
		if('\004' == c){
			break;
		}
		else{
			printf("I read %c\n",c);
		}

	}
	resume_input_mode();
	return 0;
}
