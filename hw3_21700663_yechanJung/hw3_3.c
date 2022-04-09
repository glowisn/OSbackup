#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_CMD 2048
#define MAX_ARG 256
#define BUFFER_SIZE 20

char buffer[BUFFER_SIZE];
int buffer_size = 0;
int buffer_pos = 0;

void ParseCommand(char *command,int *argc, char *argv[]);
int ReadTextLine(int fd, char str[], int max_len);

int main (int argc, char *argv[]){
	
	char *filename = argv[1];
	int fd;
	fd = open(filename, O_RDONLY);
	if(fd == -1){
		printf("file open failed\n");
		return 0;
	}

	char str[MAX_CMD];
	int cnum, ret;
	char *command[MAX_ARG];
	while(1){
		ret = ReadTextLine(fd,str,MAX_CMD);
		if(ret == EOF) break;	//if EOF, break
		//display the command
		printf("command = [%s]\n",str);
		ParseCommand(str,&cnum,command);
		//run the command  using forK()
		pid_t child_pid = fork();
		
		if(child_pid < 0){	//error	
			printf("fork failed\n");
			exit(-1);
		}else if(child_pid == 0) {
			execvp(command[0],command);
		}else {
			wait(NULL);
			//printf("Child Complete\n");
			//exit(0);
		}	
		
		
	}
		
	/*
	pid_t child_pid = fork();

	if(child_pid < 0){	//error
		printf("fork failed\n");
		exit(-1);
	}else if(child_pid == 0) {
		//execvp
	}else {
		wait(NULL);
		printf("Child Complete\n");
		exit(0);
	}	

	*/

	close(fd);
	return 0;
}


void ParseCommand(char *command,int *argc, char *argv[]){
	int i = 0, j = 0, k = 0;
	char str[MAX_ARG][MAX_CMD];

	while(command[i] != '\0'){
		if(command[i] == ' '){
			str[k][j] = '\0';
			j = 0;
			k++;
		}else{
			str[k][j] = command[i];
			j++;
		}
		i++;
	}

	str[k][j] = '\0';
	
	*argc = k+1;

	for(int ind = 0; ind <= k; ind++){
		argv[ind] = str[ind];
	}

	argv[*argc] = NULL;
}

int ReadTextLine(int fd, char str[], int max_len)
{
	int i = 0;
	int j = 0;
	int ret = 0;

	if(lseek(fd,0,SEEK_CUR) == 0)
		buffer_pos = buffer_size = 0;
	
	while(j < max_len - 1){
		if(buffer_pos == buffer_size){
			buffer[0] = 0;
			buffer_size = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
		}
		if(buffer_size == 0){
			if(j==0)
				ret = EOF;
			break;
		}
		while(j<max_len - 2
				&& buffer_pos < buffer_size){
			str[j++] = buffer[buffer_pos++];
			if(str[j - 1] == '\0' || str[j - 1] == 10){
				j--;
				max_len = j;
				break;
			}
		}
	}

	str[j] = 0;

	return ret;
}
