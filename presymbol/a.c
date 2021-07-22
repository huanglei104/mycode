#include <stdio.h>
#include <stdlib.h>

int _start(int argc, char *argv[])
{
    printf("FILE %s\n", __FILE__);
    printf("LINE %d\n", __LINE__);
    printf("DATE %s\n", __DATE__);
    printf("TIME %s\n", __TIME__);
    printf("STDC %d\n", __STDC__);
    printf("func %s\n", __func__);
    printf("func %s\n", __FUNCTION__);
    printf("func %s\n", __PRETTY_FUNCTION__);
#ifdef __linux__
    printf("linux %d\n", __linux__);
#endif

#ifdef __LP64__
    printf("LP64 %d\n", __LP64__);
#endif

#ifdef __GNUC__
    printf("GNUC %d\n", __GNUC__);
#endif

#ifdef __i386__
    printf("i386 %d\n", __i386__);
#endif

#ifdef __x86_64__
    printf("x86_64 %d\n", __x86_64__);
#endif

    exit(0);
    return 0;
}
