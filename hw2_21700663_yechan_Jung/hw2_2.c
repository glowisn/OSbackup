#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_CMD 2048

int main()
{
	char path[MAX_CMD];
	if(getcwd(path, MAX_CMD) == NULL)
		printf("Error! getcwd Failed!\n");


	DIR* dirpath = NULL;
	if((dirpath = opendir(path)) == NULL)
		printf("Error! opendir Failed!\n");

	struct dirent* listfile = NULL;
	while((listfile = readdir(dirpath)) != NULL){
		printf("%s",listfile->d_name);
		if(listfile->d_type == 4)
			printf(" [directory]");
		printf("\n");
	}



	closedir(dirpath);

	return 0;
}
