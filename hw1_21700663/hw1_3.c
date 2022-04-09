#include <stdio.h>
#include <string.h>


#define MAX_CMD 2048
#define MAX_ARG 256

void ParseCommand(char *command,int *argc, char *argv[]);

int main()
{
	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1]=0;

	int argc = 0;
	char *argv[MAX_ARG] = {NULL};

	while(1){
		printf("$ ");
		fgets(command, MAX_CMD - 1, stdin);
		command[strlen(command) - 1] = 0;
		
		if(strcmp(command, "quit") == 0 
				|| strcmp(command, "exit") == 0)
			break;

		ParseCommand(command, &argc, argv);

		printf("argc = %d\n",argc);
		for(int i = 0; i < argc; i++)
			printf("argv[%d] = %s\n",i,argv[i]);
		printf("argv[%d] = %p\n",argc,argv[argc]);
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
	
	/*
	for(int ind = 0; ind <= k; ind++){
		printf("str[ind] = %s \n",str[ind]);
	}

	*/
	*argc = k+1;

	for(int ind = 0; ind <= k; ind++){
		argv[ind] = str[ind];
	}
}
