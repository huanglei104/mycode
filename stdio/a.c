#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{

    FILE *fp;
    ssize_t size;

    const char *buf = "hello world";

    printf("buf %ld\n", strlen(buf));

    fp = fopen("test.txt", "w+");
    if(fp == NULL) return perror("fopen"), -1;

    size = fwrite(buf, sizeof(buf) - 1, 1, fp);
    if(size != sizeof(buf) - 1) return perror("fwrite"), -1;

    if(fclose(fp) == EOF) return perror("fclose"), -1;

    return 0;
}
