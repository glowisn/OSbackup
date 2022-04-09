#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	float delay = atof(argv[1]);

	if(delay == 0){	//if delay ctof failed
		printf("Input numbers for delay.\n");
		return 0;
	}

	//make time_t and tm
	time_t priTime;
	priTime  = time(&priTime);
	struct tm* pTiin;
	pTiin = localtime(&priTime);

	int year = pTiin -> tm_year + 1900;
	int month = pTiin -> tm_mon + 1;
	int day = pTiin -> tm_mday;
	
	int hour = pTiin -> tm_hour;
	int min = pTiin -> tm_min;
	int sec = pTiin -> tm_sec;
	printf("current date = %d/%d/%d\n",year,month,day);
	printf("current time = %d:%d:%d\n",hour,min,sec);
	
	
	//make delay time
	struct timeval start_time, end_time;
	double elapsedTime;
	
	//start op
	gettimeofday(&start_time, NULL);
	struct tm* start_pTiin;
	start_pTiin = localtime(&start_time.tv_sec);
	
	//start_time tm to 
	int start_hour = start_pTiin -> tm_hour;
	int start_min = start_pTiin -> tm_min;
	int start_sec = start_pTiin -> tm_sec;
	
	//wait
	printf("\nwaiting for %f sec using usleep()\n\n",delay);
	usleep(delay*1000000);	

	//end op
	gettimeofday(&end_time, NULL);
	struct tm* end_pTiin;
	end_pTiin = localtime(&end_time.tv_sec);
	
	// end_time to int
	int end_hour = end_pTiin -> tm_hour;
	int end_min = end_pTiin -> tm_min;
	int end_sec = end_pTiin -> tm_sec;


	printf("start_time = (%ld %ld), %d:%d:%d\n"
			,start_time.tv_sec, start_time.tv_usec
			,start_hour, start_min, start_sec);


	printf("end_time = (%ld %ld), %d:%d:%d\n"
			,end_time.tv_sec, end_time.tv_usec
			,end_hour, end_min, end_sec);

	//print flaot elapsed time	
	elapsedTime = (end_time.tv_sec - start_time.tv_sec)
	       	+((float)(end_time.tv_usec - start_time.tv_usec) / 1000000);
	printf("elapsed time = %f sec\n",elapsedTime);	

	return 0;
}
