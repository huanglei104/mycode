#include "common.h"

int xsi_sem(int time);
int name_sem(int time);
int unname_sem(int time);

int forkn(int n, int (*run)(int time), int time)
{
	int cnt = 0;
	pid_t pid;

	for (int i = 0; i < n; i++) {

		pid = fork();
		if (pid < 0) perror("fork");

		else if (pid == 0) {
			run(time);
			break;
		}

		else {
			cnt++;
			continue;
		}
	}

	if (pid > 0)
		return cnt;

	exit(EXIT_SUCCESS);
}

int waitall()
{
	while (waitpid(-1, NULL, 0) > 0);

	if (errno != ECHILD) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	int index = 0;

	if (argc == 2)
		index = atoi(argv[1]);

	switch (index) {
		case 1:
			name_sem(1);
			break;
		case 2:
			unname_sem(2);
			break;
		default:
			xsi_sem(1);
			break;
	}

	return 0;
}
