#include <string.h>
#include <stdio.h>
#include <asm/errno.h>
#include <errno.h>

int main(int argc, char *argv[]) {

	char *str1 = "kklhello world";
	char *str2 = "jkl";
	errno = EAGAIN;

	printf("%ld\n", strspn(str1, str2));
	printf("%ld\n", strcspn(str1, str2));
	printf("%m", errno);
}
