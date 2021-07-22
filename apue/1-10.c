#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 512

static void sig_int(int signo)
{
    printf("signal %d\n", signo);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    char buf[BUFSIZE];

    if (signal(SIGINT, sig_int) == SIG_ERR) {
	perror("signal");
	exit(0);
    }

    printf(">>> ");
    while (fgets(buf, BUFSIZE, stdin) != NULL) {
	buf[strlen(buf) - 1] = '\0';  //strlen以回车做为字符串结束

	pid = fork();
	if (pid < 0) {
	    perror("fork");
	    break;
	} else if (pid == 0) {
	    if (execlp(buf, buf, NULL) == -1) {
		perror("execlp");
		exit(-1);
	    }
	} else {
	    if (waitpid(pid, &status, 0) == -1) {
		perror("waitpid");
		exit(-1);
	    }
	}
	printf(">>> ");
    }
    return 0;
}
