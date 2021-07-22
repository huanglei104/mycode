#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/tcp.h>

int main(int argc, char *argv[])
{
	int listen_socket;
	int cli_socket;
	struct sockaddr_in addr;
	char buf[1024];

	listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_socket == -1) {
		return perror("socket"), EXIT_FAILURE;
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8899);

	if (bind(listen_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		return perror("bind"), EXIT_FAILURE;
	}

	if (listen(listen_socket, 20) == -1) {
		return perror("listen"), EXIT_FAILURE;
	}

	cli_socket = accept(listen_socket, NULL, NULL);
	if (cli_socket == -1) {
		close(listen_socket);
		return perror("accept"), EXIT_FAILURE;
	}

	bzero(buf, 1024);

	while (1) {
		int ret;
		ret = read(cli_socket, buf, 1024);
		if (ret > 0)
			printf("%s\n", buf);
		else if (ret == 0) {
			ret = send(cli_socket, "OK", 3, 0);
			if (ret <= 0) {
				perror("send");
			}
			break;
		} else
			perror("read");
	}


	close(listen_socket);
	close(cli_socket);

	return 0;
}
