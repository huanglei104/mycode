#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    int n;
    char buf[BUFSIZE];
    
    while ((n = read(STDIN_FILENO, buf, BUFSIZE)) != -1) {
	if (n == 0) break;
	if (write(STDOUT_FILENO, buf, n) != n) {
	    perror("write");
	    exit(0);
	}
    }

    return 0;
}
