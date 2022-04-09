#include <stdio.h>

#include "Console.h"

int main(int argc, char *argv)
{
	clrscr();			// clear screen

	// retrieve the size of window
	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	printf("i: up, j: left, k: down, l: right, c: change color, q: quit\n");
	printf("screen size: %d x %d\n", screen_width, screen_height);

	int x = screen_width / 2;	// horizontal coordinate
	int y = screen_height / 2;	// vertical coordinate
	int key = 0;
	int repeat = 1;
	char c = '*';		// initial color

	gotoxy(x, y);		// move the cursor to (x, y)
	putchar('#');

	int oldx = 0, oldy = 0;
	while(repeat){
		// TO DO: save current coordinate in (oldx, oldy)
		oldx = x;
		oldy = y;

		gotoxy(1, 3);
		printf("x = %3d, y = %3d", x, y);

		gotoxy(screen_width, 1);	// move cursor to upper right corner
		key = getch();		// read a key not waiting for ENTER

		// these two lines are only to show how to use gotoxy() and getch()
		// remove them when you complete the homework
		//gotoxy(1, 4);
		//printf("key = %c (%3d) c= %c \n", key, key,c);
/*
		TO DO: implement the following actions

		if key is 'i', 'j', 'k', or 'l', move the coordinate accordingly
			'i': move up
			'j': move left
			'k': move down
			'l': move right

			Note! The coordinate should be in the valid range.
			(1 <= x <= screen_width, 1 <= y <= screen_height)
*/

		gotoxy(x,y);
		putchar(c);

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
		
		gotoxy(x,y);
		putchar('#');

	}

	clrscr();
	printf("Bye!\n");

	return 0;
}
