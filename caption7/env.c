#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[])
{
    char *name = "TEST";
    char *value = NULL;

    if(setenv(name, "testtest", 1)) {
        return perror("setenv"), -1;
    }
    value = getenv(name);
    if(value) {
        printf("%s=%s\n", name, value);
    }
    return 0;
    while(*environ) {
        printf("%s\n", *environ);
        environ++;
    }
    return 0;
}
