#include <arpa/inet.h>
#include <bits/types/struct_iovec.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
/*
*分别使用3种方式发送数据，send, sendto, sendmsg
*/
void send_data(int sockfd, struct sockaddr *addr, socklen_t len)
{
	int ret;
	struct msghdr msg;
	struct cmsghdr cmsg;

	struct iovec iov;

	ret = sendto(sockfd, "hello world", 12, 0,
			addr, len);
	if (ret == -1) {
		perror("sendto");
		close(sockfd);
		return;
	}

	if (connect(sockfd, addr, len) == 0) {
		ret = send(sockfd, "hello world2", 13, 0);
		if (ret == -1) {
			perror("connect");
			return;
		}
	} else {
		perror("connect");
		return;
	}

	iov.iov_base = "hello world3";
	iov.iov_len = 13;
	msg.msg_name = addr;
	msg.msg_namelen = len;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;

	if (sendmsg(sockfd, &msg, 0) == -1) {
		perror("sendmsg");
		return;
	}

}

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in addr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socket");
		return EXIT_FAILURE;
	}

	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("10.10.255.255");
	addr.sin_port = htons(1111);

	send_data(sockfd, (struct sockaddr*)&addr, sizeof(addr));

	return 0;
}
