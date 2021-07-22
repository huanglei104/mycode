#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR	*dir;
    struct dirent *de;

    if (argc != 2) return printf("parameters error\n"), 0;

    dir = opendir(argv[1]);
    if (dir == NULL) return perror("opendir"), 0;

    while ((de = readdir(dir)) != NULL) {
	printf("%s\n", de->d_name);
    }

    closedir(dir);
    return 0;
}
