#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_PATH 256
#define MAX_CMD 1024

int FindFile(char *start_dir, char *target, char *path);

int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Usage: %s <start_dir> <target_file>\n",argv[0]);
		return 0;
	}
	char *start_dir = argv[1];
	char *target = argv[2];
	char path[MAX_PATH] = "";
	int ret = FindFile(start_dir, target, path);

	if(ret)
		printf("path = %s\n", path);
	else
		printf("Cannot find %s\n", target);
	return 0;
}

int FindFile(char *start_dir, char *target, char *path){

	int end = 0;

	DIR* dir_con = NULL;
	if((dir_con = opendir(start_dir)) == NULL){
		printf("opendir Failed!\n");
		return 0;
	}

	chdir(start_dir);

	struct dirent* listfile = NULL;
	while((listfile = readdir(dir_con)) != NULL){
	
		//printf("cur_file: %s\n",listfile->d_name);

		if(strcmp(listfile->d_name,".") == 0 || 
				strcmp(listfile->d_name,"..") == 0){
			//skip . and .. parent directory
		}else if(strcmp(listfile->d_name,target) == 0){
			//Found File (base case)
			//printf("File Found here.\n");
			getcwd(path,MAX_CMD);
			return 1;
		}else{
			//not found
			//if directory
			if(listfile->d_type == 4){
				//Go to under directory
				end = FindFile(listfile->d_name,target,path);
				chdir("..");
				if(end == 1) return 1;
			}
		}
	}
	return 0;
}


