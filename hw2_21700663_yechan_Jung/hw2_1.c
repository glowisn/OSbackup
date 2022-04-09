#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#define MAX_CMD 2048
#define MAX_ARG 256

void ParseCommand(char *command,int *argc, char *argv[]);

int main()
{
	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1]=0;

	int argc = 0;
	char *argv[MAX_ARG] = {NULL};

	char path[MAX_CMD];

	while(1){

		printf("$ ");
		fgets(command, MAX_CMD - 1, stdin);
		command[strlen(command) - 1] = 0;

		if(strcmp(command, "quit") == 0 
				|| strcmp(command, "exit") == 0)
			break;

		ParseCommand(command, &argc, argv);
	
		//printf("input = %s ...\n",argv[0]);
		//printf("input = %s ...\n",argv[1]);

		if(strcmp(argv[0],"mkdir") == 0){
			//printf("make directory.\n");
			int r1  = mkdir(argv[1],0776);
			if(r1 == -1) printf("mkdir Failed!\n"); 
		}else if(strcmp(argv[0],"rmdir") == 0){
			//printf("remove directoty.\n");
			int r2 = rmdir(argv[1]);
			if(r2 == -1) printf("rmdir Failed!\n");
		}else if(strcmp(argv[0],"cd") == 0){
			//printf("change dir.\n");
			int r3 = chdir(argv[1]);
			if(r3 == -1) printf("cd Failed!\n");
		}else if(strcmp(argv[0],"curdir") == 0){
			//printf("current dir.\n");
			getcwd(path,1024);
			printf("current directory = %s\n",path);
		}else if(strcmp(argv[0],"ls") == 0){
			//printf("list files.\n");
			int rls = system("ls");
		}else{
			printf("!Unkown command!\n");
		}
	}

	printf("Bye!\n");

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
			//printf("str com :: %c %c\n",str[k][j],command[i]);
			j++;
		}
		i++;
	}
	str[k][j] = '\0';

	*argc = k+1;

	for(int ind = 0; ind <= k; ind++){
		argv[ind]=str[ind];
	}

	argv[*argc] = NULL;
}
