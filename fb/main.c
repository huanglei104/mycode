#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int *mem;
    int i, j;

    int fb = open("/dev/fb0", O_RDWR);
    if(fb == -1) return perror("open fb0"), -1;

    mem = mmap(0, 1920 * 1080 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
    if(mem == MAP_FAILED) return perror("mmap"), -1;

	for (i = 0; i < 1920 * 1080; i ++) {
		//*(mem + i) = i;
		*(mem + i) = 255;
	}

	return 0;
}
