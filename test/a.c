#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int *p  = (int*)0x1234;

	*p = 100;

	return 0;

}
