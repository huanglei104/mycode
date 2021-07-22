#include <stdio.h>
#include <glob.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int i;
	glob_t g;

	if (argc != 2) {
		printf("usage: glob pathname\n");
		return 0;
	}


	glob(argv[1], GLOB_NOSORT, NULL, &g);

	for (i = 0; i < g.gl_pathc; i++) {
		printf("%s ", (g.gl_pathv[i]));
	}

	printf("\n");

	globfree(&g);

	return 0;
}
