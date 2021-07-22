#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	long type;
	char msg[16];
} message;

int main(int argc, char *argv[])
{
	int ret;
	message msg;

	msg.type = 5;
	strcpy(msg.msg, "world");

	if ((ret = msgget(0x8888, 0666 | IPC_CREAT)) == -1) return perror("msgget"), -1;

	if (msgsnd(ret, &msg, 5, 0) == -1) return perror("msgsnd"), -1;

	return 0;
}
