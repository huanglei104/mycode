#include <stdio.h>
#include <syslog.h>
#include <sys/klog.h>
#include <stdlib.h>


#define SYSLOG_ACTION_READ_ALL 3
#define SYSLOG_ACTION_SIZE_BUFFER 10

int main(int main, char *argv[])
{
	int ret;
	char *buf;

	ret = klogctl(SYSLOG_ACTION_SIZE_BUFFER, NULL, 0);
	if (ret == -1) {
		perror("klogctl SYSLOG_ACTION_SIZE_BUFFER");
		return 0;
	}

	printf("ring buffer size %d\n", ret);

	buf = malloc(ret);
	if (buf == NULL) {
		perror("malloc");
		return 0;
	}

	ret = klogctl(SYSLOG_ACTION_READ_ALL, buf, ret);
	if (ret == -1) {
		perror("klogctl SYSLOG_ACTION_READ_ALL");
		return 0;
	}

	printf("content size %d\n", ret);
	printf("%s\n", buf);

	return 0;
}
