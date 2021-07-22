#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/un.h>
#include <stddef.h>
#include <unistd.h>


int main(int argc, char *argv[]) {


	ssize_t addr_len;
	struct sockaddr_un ser_addr, cli_addr;

	memset(&ser_addr, 0, sizeof(ser_addr));
	memset(&cli_addr, 0, sizeof(cli_addr));

	int s = socket(PF_UNIX, SOCK_STREAM, 0);

	if(s < 0) {
		perror("socket");
		exit(-1);
	}

	sprintf(cli_addr.sun_path, "client-%d", getpid());
	cli_addr.sun_family = PF_UNIX;
	addr_len = offsetof(struct sockaddr_un, sun_path) + strlen(cli_addr.sun_path);
	if(bind(s, (struct sockaddr*)&cli_addr, addr_len) < 0) {
		perror("bind");
		exit(-1);
	}
	unlink(cli_addr.sun_path);

	strcpy(ser_addr.sun_path, "/tmp/un.socket");
	ser_addr.sun_family = PF_UNIX;
	addr_len = offsetof(struct sockaddr_un, sun_path) + strlen(ser_addr.sun_path);
	if(connect(s, (struct sockaddr*)&ser_addr, addr_len) < 0) {
		perror("connect");
	}
	return 0;

}
