#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
	int server_fd, ret;
	socklen_t len;
	struct sockaddr_in ser_addr, cli_addr;
	struct {
		char data[1024];
		int len;
	} recv_buf;

	server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (server_fd < 0) {
		perror("socket");
		return EXIT_FAILURE;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = INADDR_ANY;
	ser_addr.sin_port = htons(4567);

	ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	if (ret < 0) {
		perror("bind");
		return EXIT_FAILURE;
	}

	recv_buf.len = 0;

	while (1) {
		ret = recvfrom(server_fd, recv_buf.data, 1024, 0,
				(struct sockaddr*)&cli_addr, &len);
		if (ret == -1) {
			perror("recvfrom");
			return EXIT_FAILURE;
		}

		recv_buf.len = ret;

		printf("%*s\n", recv_buf.len, recv_buf.data);
	}

	return EXIT_SUCCESS;
}
