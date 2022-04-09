#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"


int main(int argc, char *argv)
{
	// TO DO: open SHM_FILE for using shm_open()
	//  check if the file was successfully open
	int shm_fd;

	shm_fd = shm_open(SHM_FILE, O_RDWR, 0666);
	if(shm_fd == -1){
	    printf("shm_open Failed!\n");
	    return 0;
	}


	int buffer_size = sizeof(KeyBuffer);

	// TO DO: map the shared memory file and receive the return address into     key_buffer
	// check if the file was successfully mapped
	KeyBuffer *key_buffer = NULL;
	key_buffer = mmap(0, buffer_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(key_buffer == MAP_FAILED){
	    printf("mmap Failed!\n");
	    return 0;
	}


	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	clrscr();

	printf("screen size: %d x %d\n", screen_width, screen_height);
	int x = screen_width / 2;
	int y = screen_height / 2;
	int key = 0;
	char c = '*';
	int repeat = 1;

	gotoxy(x, y);
	putchar('#');

	while(repeat){
		int oldx = x;
		int oldy = y;
	
		// TO DO: read a key from the key buffer in the shared memory
		// if the key is zero, repeat until a non-zero key is read
		
		do{
		    gotoxy(screen_width, 1);
		    key = DeleteKey(key_buffer);
		}while(key == 0);
/*
		TO DO: implement the following actions

		if key is 'i', 'j', 'k', or 'l', move the coordinate accordingly
			'i': move up
			'j': move left
			'k': move down
			'l': move right

			Note! The coordinate should be in the valid range.
			(1 <= x <= screen_width, 1 <= y <= screen_height)

		if key is 'c', change color
			toggle c between ' ' and '*' 

		if key is 'q', break the loop
			
*/


		switch(key){
		    case 'q':
		    repeat = 0;
		    break;

		    case 'c':
		    if(c=='*')
			c = ' ';
		    else if(c==' ')
			c = '*';
		    break;

		    case 'i':
		    if(1<y)
			y-=1;
		    break;

		    case 'j':
		    if(1<x)
			x-=1;
		    break;

		    case 'k':
		    if(y<screen_height)
			y+=1;
		    break;

		    case 'l':
		    if(x<screen_width)
			x+=1;
		    break;
		 }
		
		// TO DO: print c at (oldx, oldy)
		gotoxy(oldx,oldy);
		putchar(c);

		// TO DO: print '#' at (x, y)
		gotoxy(x,y);
		putchar('#');
	}

	munmap(key_buffer,buffer_size);
	shm_unlink(SHM_FILE);

	clrscr();
	printf("Bye!\n");

	return 0;
}
