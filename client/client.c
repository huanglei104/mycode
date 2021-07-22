#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/signal.h>

void* thread_recv(void *args)
{
	int size;
	int client = (int)(long)args;
	char buffer[1024];

	while(1) {
		memset(buffer, 0, 1024);
		size = recv(client, buffer, 1024, 0);
		if (size < 0) {
			perror("recv");
			exit(-1);
		}
		printf("recv:%s\n", buffer);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in srcaddr;
	struct sockaddr_in addr;
	char buffer[1024] = {0};

	addr.sin_family = PF_INET;
	addr.sin_port = htons(21);
	addr.sin_addr.s_addr = inet_addr("10.10.88.4");

	srcaddr.sin_family = AF_INET;
	srcaddr.sin_port = htons(4567);

	if (inet_aton("10.10.88.90", &srcaddr.sin_addr) == 0) {
		perror("inet_aton");
		return 0;
	}

	int client = socket(PF_INET, SOCK_STREAM, 0);
	if (client == -1) {
		perror("socket");
		return 0;
	}

	if (bind(client, (struct sockaddr*)&srcaddr, sizeof(srcaddr)) == -1) {
		perror("bind");
		return -1;
	}


	int ret = connect(client, (struct sockaddr*)&addr, sizeof(addr));
	if(ret != 0) {
		perror("connect");
		return 0;
	}

	shutdown(client, SHUT_WR);

	ret = recv(client, buffer, 1024, 0);
	if (ret <= 0) {
		perror("recv");
		close(client);
		return 0;
	}

	printf("%s\n", buffer);

	ret = send(client, " ", 1, 0);
	if (ret <= 0) {
		perror("send");
		close(client);
		return 0;
	}

	printf("send success\n");

	ret = recv(client, buffer, 1024, 0);
	if (ret <= 0) {
		perror("recv");
		close(client);
		return 0;
	}

	printf("%s\n", buffer);

	return 0;
}
