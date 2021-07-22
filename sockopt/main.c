#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <time.h>

void set_keepalive(int sockfd, int time)
{
	int value = 1;

    if (setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &value, sizeof(value)) == -1) {
		return perror("setsockopt SO_KEEPALIVE");
    }

    if (setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE, &time, sizeof(time)) < 0) {
		return perror("setsockopt TCP_KEEPIDLE");
    }

    if (setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPINTVL, &time, sizeof(time)) < 0) {
		return perror("setsockopt TCP_KEEPINTVL");
    }

    if (setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPCNT, &time, sizeof(time)) < 0) {
		return perror("setsockopt TCP_KEEPCNT");
    }

}

void get_socket_opt(int fd)
{
	int bufsize, ret;
	socklen_t len;

	struct timeval time;

	len  = sizeof(bufsize);

	bufsize = 10000;

	ret = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &bufsize, 4);
	if (ret == -1) {
		perror("getsocket");
		return;
	}

	ret = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &bufsize, &len);
	if (ret == -1) {
		perror("getsocket");
		return;
	}

	printf("recvbuf: %d\n", bufsize);

	bufsize = 20000;

	ret = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &bufsize, 4);
	if (ret == -1) {
		perror("getsocket");
		return;
	}

	ret = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &bufsize, &len);
	if (ret == -1) {
		perror("getsocket");
		return;
	}

	printf("sendbuf: %d\n", bufsize);

	time.tv_sec = 5;
	time.tv_usec = 0;

	ret = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &time, sizeof(time));
	if (ret == -1) {
		perror("setsocket");
		return;
	}

	ret = getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &time, &len);
	if (ret == -1) {
		perror("getsocket");
		return;
	}

	printf("recvtime: %ld\n", time.tv_sec);

	time.tv_sec = 15;
	time.tv_usec = 0;
	len = sizeof(time);

	ret = setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &time, sizeof(time));
	if (ret == -1) {
		perror("setsocket");
		return;
	}

	time.tv_sec = 0;
	time.tv_usec = 0;
	len = sizeof(time);

	ret = getsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &time, &len);
	if (ret == -1) {
		perror("getsocket");
		return;
	}

	printf("sendtime: %ld\n", time.tv_sec);
}

int main(int argc, char *argv[])
{
	int sockfd;
	char buf[32] = {0};
	struct sockaddr_in addr;
	time_t start, end;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket");
		return 0;
	}

	get_socket_opt(sockfd);

	set_keepalive(sockfd, 5);

	return 0;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("10.10.88.90");
	addr.sin_port = htons(8888);

	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("socket");
		return 0;
	}

	start = time(NULL);

	if (recv(sockfd, buf, 32, 0) <= 0) {
		perror("recv");
		return 0;
	}

	end = time(NULL);

	printf("%ld\n", end - start);

	return 0;
}
