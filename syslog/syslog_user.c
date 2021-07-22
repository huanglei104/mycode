#include <sys/syslog.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
	openlog("huanglei104 test", LOG_PID, LOG_USER);

	syslog(LOG_INFO, "hello");

	closelog();
	return 0;
}
