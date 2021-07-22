#define _POSIX_C_SOURCE 200809L
#include <features.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>


struct rlimit rl;

void foo(char *s)
{
    printf("%s\n", s);
}

int32_t main(int32_t argc, char *argv[])
{
    char *addr;

    //foo(addr);
    printf("---------%s\n", __func__);
    printf("XSI version %d\n", _SC_XOPEN_VERSION);

    printf("exec arguments max length : %ld\n", sysconf(_SC_ARG_MAX));
    printf("user max process : %ld\n", sysconf(_SC_CHILD_MAX));
    printf("hostname max length : %ld\n", sysconf(_SC_HOST_NAME_MAX));
    printf("login name max length : %ld\n", sysconf(_SC_LOGIN_NAME_MAX));
    printf("groups max : %ld\n", sysconf(_SC_NGROUPS_MAX));
    printf("the number of clock ticks per second : %ld\n", sysconf(_SC_CLK_TCK));
    printf("The maximum number of files that a process can have open at any time : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Size of a page in bytes : %ld\n", sysconf(_SC_PAGESIZE));
    printf("The number of repeated occurrences of a BRE permitted by regexec(3) and regcomp(3).: %ld\n", sysconf(_SC_RE_DUP_MAX));
    return 0;
}


