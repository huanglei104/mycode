#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

typedef struct {
	long type;
	char msg[16];
} message;

int main(int argc, char *argv[])
{
	int ret;
	message msg;

	memset(&msg, 0, sizeof(message));

	if ((ret = msgget(0x8888, 0666 | IPC_CREAT)) == -1) return perror("msgget"), -1;

	if (msgrcv(ret, &msg, 16, 5, 0) == -1) return perror("msgrcv"), -1;

	printf("%s\n", msg.msg);

	return 0;
}
