#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/uio.h>

struct {
	char name[16];
	int opt;
	int value;
	socklen_t len;
} options[] = {
	{"nodelay", TCP_NODELAY, -1, -1},
	{"cork", TCP_CORK, -1, -1},
	{"quickack", TCP_QUICKACK, -1, -1},
};

void getsocktop(int sockfd)
{
	for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++) {
		if (getsockopt(sockfd, IPPROTO_TCP, options[i].opt, &options[i].value,
					&options[i].len) == 0) {
			printf("default %s %d\n", options[i].name, options[i].value);
		}
	}
}

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		return perror("socket"), EXIT_FAILURE;
	}

	getsocktop(sockfd);

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("10.10.88.90");
	addr.sin_port = htons(8899);

	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
		char buf[100];
		//if (close(sockfd) == -1) {
		if (shutdown(sockfd, SHUT_WR) == -1) {
			perror("close");
			return 0;
		}

		if (read(sockfd, buf, 100) <= 0) {
			perror("read");
			return 0;
		}

		printf("%s\n",buf);
	} else {
		perror("connect");
	}

	close(sockfd);

	return 0;
}
