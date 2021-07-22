#include <stdio.h>

int main(int argc, char* argv[])
{
	int a = 10;
	int *p = &a;

	void *vp = &a;

	printf("p %p\n", p);
	printf("++p %p\n", p + 2);

	printf("vp %p\n", vp);
	printf("++vp %p\n", vp + 2);

	return 0;
}
