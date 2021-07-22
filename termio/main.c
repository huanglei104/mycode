#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	int fd;
	struct termios tos;

	fd = open("/dev/tty", O_RDONLY);
	if (fd == -1) {
		return perror("open tty"), -1;
	}

	if (tcgetattr(fd, &tos) == -1) {
		return perror("tcgetattr"), -1;
	}

	tos.c_cc[VINTR] = ~_PC_VDISABLE;
	tos.c_cc[VSTOP] = ~_PC_VDISABLE;

	if(tcsetattr(fd, TCSANOW, &tos) == -1) {
		return perror("tcsetattr"), -1;
	}

	return 0;
}
