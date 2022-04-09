#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 20

char buffer[BUFFER_SIZE];
int buffer_size = 0;
int buffer_pos = 0;

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

int main(){
	int cpufd, memfd, loadfd;
	char str[1024];

	cpufd = open("/proc/cpuinfo",O_RDONLY);
		
	for(int i = 0; i < 13; i++){
	ReadTextLine(cpufd, str, 1024);

	}
	printf("%s\n",str);

	lseek(cpufd, 0 , SEEK_SET);

	for(int i = 0; i < 5;i++){
		ReadTextLine(cpufd, str, 1024);
	}
	
	printf("%s\n",str);

	
	memfd = open("/proc/meminfo",O_RDONLY);
	ReadTextLine(memfd, str, 1024);
	printf("%s\n",str);

	loadfd = open("/proc/loadavg",O_RDONLY);
	ReadTextLine(loadfd, str, 1024);

	int i = 0, j = 0, k = 0;
	char newstr[3][10];
	
	while(k<3){
		while(str[i]!=' '){
			newstr[k][j] = str[i];
			j++; i++;	
		}
		i++;
		newstr[k][j] = '\0';
		j=0;
		k++;
	}

	printf("loadavg1 = %s, loadavg5 = %s, loadavg15 = %s\n"
			,newstr[0],newstr[1],newstr[2]);

	return 0;		
}

