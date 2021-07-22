#include <stdio.h>

void foo(char str[10])
{
	printf("%ld\n", sizeof(str));
}

int main(int argc, char *argv[])
{
	char str[] = "hello";
	foo(str);
	return 0;
}
