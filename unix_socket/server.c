#include <stdlib.h>  
#include <stdio.h>  
#include <stddef.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <errno.h>  
#include <string.h>  
#include <unistd.h>  
#include <ctype.h>   

#define MAXLINE 80  

char *socket_path = "/tmp/un.socket";  

int main(int argc, char *argv[]) {  
	struct sockaddr_un serun;  
	int listenfd, connfd, size;  
	char buf[MAXLINE];  

	if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {  
		perror("socket error");  
		exit(1);  
	}  

	memset(&serun, 0, sizeof(serun));  
	serun.sun_family = PF_UNIX;  
	strcpy(serun.sun_path, socket_path);  
	size = offsetof(struct sockaddr_un, sun_path) + strlen(serun.sun_path);  
	printf("%d\n", size);
	printf("%ld\n", sizeof(serun));
	if (bind(listenfd, (struct sockaddr*)&serun, 110) < 0) {  
		perror("bind error");  
		exit(1);  
	}  
	printf("UNIX domain socket bound\n");  

	if (listen(listenfd, 20) < 0) {  
		perror("listen error");  
		exit(1);          
	}  
	printf("Accepting connections ...\n");  

		connfd = accept(listenfd, NULL, NULL);
		close(listenfd);
		if(connfd < 0) {  
			perror("accept error");  
			exit(-1);
		}  
		while(1) {  
			size = read(connfd, buf, sizeof(buf));  
			if(size < 0) {  
				perror("read error");  
				break;  
			} else if(size == 0) {  
				printf("EOF\n");  
				break;  
			}  
			printf("received: %s\n", buf);  
			write(connfd, buf, size);  
		}  
		close(connfd);  
		unlink(socket_path);  
	return 0;  
} 
