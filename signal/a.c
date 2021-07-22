#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void int_handler (int signo)
{
	printf("signal handler start\n");
	sleep(2);
	printf("signal handler finish\n");
}

int main(int argc, char *argv[])
{
	int ret;
	struct sigaction nact, oact;

	nact.sa_handler = int_handler;
	sigemptyset(&nact.sa_mask);
	nact.sa_flags = SA_NODEFER;
	//sigaddset(&nact.sa_mask, SIGINT);

	ret = sigaction(SIGINT, &nact, &oact);
	if (ret == -1) {
		perror("sigaction");
		return -1;
	}

	while (1);

	return 0;
}
