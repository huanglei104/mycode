#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void timer_handler (int signum)
{
    printf("trigger...\n");
}

int main(int argc, char *argv[])
{
    struct sigaction sa;
    struct itimerval timer;

    /* Install timer_handler as the signal handler for SIGVTALRM. */
    memset(&sa, 0, sizeof (sa));

    sa.sa_handler = timer_handler;

    sigaction (SIGVTALRM, &sa, NULL);

    /* Configure the timer to expire after 100 msec... */
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;

    /* ... and every 100 msec after that. */
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    /* Start a virtual timer. It counts down whenever this process is
    executing. */

    setitimer (ITIMER_VIRTUAL, &timer, NULL);

	printf("wait...\n");

    /* Do busy work. */
	while (1) {
		printf("aaa\n");
		sleep(1);
	}
	return 0;
}
