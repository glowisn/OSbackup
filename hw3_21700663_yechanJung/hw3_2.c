#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <time.h>

void parseTimePrint(time_t time);

int main(int argc, char *argv[]){
	if(argc == 1){	//with no argument
		printf("User and Process info:\n");
		printf("\tgetuid() = %d\n", getuid());
		printf("\tgetpid() = %d\n", getpid());
		printf("\tgetppid() = %d\n", getppid());	
	
		struct utsname kInfo;
		uname(&kInfo);
		printf("\nKernel info:\n");
		printf("\tsysname = %s\n",kInfo.sysname);
		printf("\tnodename = %s\n",kInfo.nodename);
		printf("\trelease = %s\n",kInfo.release);
		printf("\tversion = %s\n",kInfo.version);
		printf("\tmachine= %s\n",kInfo.machine);

		struct sysinfo sInfo;
		sysinfo(&sInfo);
		printf("\nSystem info:\n");
		printf("\tuptime = %ld\n",sInfo.uptime);
		printf("\ttotalram = %ld\n",sInfo.totalram);
		printf("\tfreeram = %ld\n",sInfo.freeram);
		printf("\tprocs = %d\n",sInfo.procs);

	}


	if(argc == 2){	//with argument file info
		
		//if there is no file
		if( access(argv[1],F_OK) == -1){
			printf("No such file\n");
			return 0;
		}

		//access
		printf("Permission of file %s\n",argv[1]);
		printf("\tpermission to read: %d\n",access(argv[1],R_OK)+1);
		printf("\tpermission to write: %d\n",access(argv[1],W_OK)+1);
		printf("\tpermission to execute: %d\n",access(argv[1],X_OK)+1);

		//stat
		struct stat sof;
		stat(argv[1],&sof);
		printf("stat of file %s\n",argv[1]);
		printf("st_ino = %ld\n",sof.st_ino);
		printf("st_mode = %o(octal)\n",sof.st_mode);
		printf("st_uid = %d\n",sof.st_uid);
		printf("st_gid = %d\n",sof.st_gid);
		printf("st_size = %ld\n",sof.st_size);
		//time	
		printf("st_atime = ");parseTimePrint(sof.st_atime);	
		printf("st_mtime = ");parseTimePrint(sof.st_mtime);	
		printf("st_ctime = ");parseTimePrint(sof.st_ctime);	
	}

	return 0;
}

void parseTimePrint(time_t time){
	struct tm *t;
	t = localtime(&time);
	printf("%d/%d/%d %d:%d:%d\n"
			,t->tm_year + 1900, t->tm_mon + 1, t->tm_mday
			,t->tm_hour, t->tm_min, t->tm_sec);

}
