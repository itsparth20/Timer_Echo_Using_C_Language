//Developed by Parth Patel
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <signal.h>

void echoFunn(int);
void checkSignal(int);
int sec = 0;
int checkBit = 0;

void checkSignal(int sig)
{
	if(sig == SIGQUIT){
		echoFunn(1);
		printf("%02i:%02i:%02i\r\n\n", sec/3600, sec/60%60, sec%60);
		exit(0);
	}
	if(sig == SIGINT){
		if(checkBit){
			checkBit = 0;
		}
		else{
			checkBit = 1;
		}
	}
}

int main(int argC, char* argv[])
{
	if(argC != 2)
	{
		printf("\tUsage: ./objectName second(second should be integer)\n");
		exit(0);
	}

	signal(SIGINT, checkSignal);
	signal(SIGQUIT, checkSignal);

	echoFunn(0);
	sec = atoi(argv[1]);  
	printf("\n");
	
	while(1)
	{
		if(checkBit){
			continue;
		}
  
		sleep(1);      
		echoFunn(1);
		printf("%02i:%02i:%02i\r", sec/3600, sec/60%60, sec%60);
		sec--;
		fflush(0);
		echoFunn(0);
		if(sec < 0){
			break;    
		}
	}
	printf("\n\n");
	echoFunn(1);
}

void echoFunn(int sign)
{
	int temp;
	struct termios value;
	if(temp = tcgetattr(0, &value) == -1) 
	{
		printf("Error\n");
		exit(0);
	}
	if(sign){
		value.c_lflag |= ECHO;
	}
	else{
		value.c_lflag &= ~ECHO;
	}
	if(temp = tcsetattr(0, TCSANOW, &value) == -1)
	{
		printf("Error\n");
		exit(0);
	}
}
