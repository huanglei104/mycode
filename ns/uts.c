#define _GNU_SOURCE

#include <sched.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define NOT_OK_EXIT(code, msg); {if(code == -1){perror(msg); exit(-1);} }

static int child_func(void *hostname)
{
    sethostname(hostname, strlen(hostname));

    execlp("bash", "bash",  NULL);


    return 0;
}

static char child_stack[1024*1024];

int create_new_ns(int argc, char *argv[])
{
    pid_t child_pid;

    if (argc < 2) {
        printf("Usage: %s <child-hostname>\n", argv[0]);
        return -1;
    }

    child_pid = clone(child_func,
                    child_stack + sizeof(child_stack),
                    CLONE_NEWUTS | SIGCHLD,
                    argv[1]);
    NOT_OK_EXIT(child_pid, "clone");

    waitpid(child_pid, NULL, 0);

	return 0;
}

int add_to_ns(int argc, char *argv[])
{
	int fd, ret;

    if (argc < 2) {
        printf("%s /proc/PID/ns/FILE\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    NOT_OK_EXIT(fd, "open");

    ret = setns(fd, 0);
    NOT_OK_EXIT(ret, "open");

    execlp("bash", "bash", NULL);

    return 0;
}

static void usage(const char *pname)
{
    char usage[] = "Usage: %s [optins]\n"
                   "Options are:\n"
                   "    -i   unshare IPC namespace\n"
                   "    -m   unshare mount namespace\n"
                   "    -n   unshare network namespace\n"
                   "    -p   unshare PID namespace\n"
                   "    -u   unshare UTS namespace\n"
                   "    -U   unshare user namespace\n";
    printf(usage, pname);
    exit(0);
}


int  exit_and_add_to_ns(int argc, char *argv[])
{
	int flags = 0, opt, ret;

    while ((opt = getopt(argc, argv, "imnpuUh")) != -1) {
        switch (opt) {
            case 'i': flags |= CLONE_NEWIPC;        break;
            case 'm': flags |= CLONE_NEWNS;         break;
            case 'n': flags |= CLONE_NEWNET;        break;
            case 'p': flags |= CLONE_NEWPID;        break;
            case 'u': flags |= CLONE_NEWUTS;        break;
            case 'U': flags |= CLONE_NEWUSER;       break;
            case 'h': usage(argv[0]);               break;
            default:  usage(argv[0]);
        }
    }

    if (flags == 0) {
        usage(argv[0]);
    }

    //执行完unshare函数后，当前进程就会退出当前的一个或多个类型的namespace,
    //然后进入到一个或多个新创建的不同类型的namespace
    ret = unshare(flags);
    NOT_OK_EXIT(ret, "unshare");

    execlp("bash", "bash", (char *) NULL);

    return 0;
}

int main(int argc, char *argv[])
{
	//create_new_ns(argc, argv);

	//add_to_ns(argc, argv);

	exit_and_add_to_ns(argc, argv);

    return 0;
}
