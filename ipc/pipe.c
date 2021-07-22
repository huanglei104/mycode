#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int pid, ret, fds[2];

	ret = pipe(fds);
	if (ret == -1) {
		perror("pipe");
		return 0;
	}

	pid = fork();
	if (pid < 0) {
		perror("fork");
		return 0;

	} else if (pid == 0) {
		char buf[16];

		close(fds[1]);
		ret = read(fds[0], buf, 16);
		if (ret == -1) {
			perror("read");
			exit(0);
		}
		printf("%s\n", buf);

	} else {
		close(fds[0]);
		ret = write(fds[1], "hello", 6);
		if (ret == -1) {
			perror("write");
		}
		wait(NULL);
	}

	return 0;
}
