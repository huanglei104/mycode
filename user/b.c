#include <stdio.h>
#include <unistd.h>
#include <ttyent.h>

int main(int argc, char *argv[])
{
    struct ttyent *tty;

    tty = getttyent();
    if(tty) {
	printf("tty name %s\n", tty->ty_name);
    } else {
	return perror("getttyent"), -1;
    }
    return 0;
}
