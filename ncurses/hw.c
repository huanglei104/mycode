#include <ncurses.h>

int main(int argc, char *argv[])
{
	int x, y;

	initscr();
	getmaxyx(stdscr, y, x);
	refresh();
	getchar();
	endwin();
	printf("max %d %d\n", x, y);
	return 0;
}
