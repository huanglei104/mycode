#include <stdio.h>

int main(int argc, char *argv[])
{
    int c;

    while ((c = getc(stdin)) != EOF) {
	if ((putc(c, stdout)) == EOF) break;
    }
    
    if (ferror(stdin)) perror("stdin");
    return 0;
}
