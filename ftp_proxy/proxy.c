#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include "p.h"

struct s {};

#define TRUE 1
#define FALSE 0

#define CMD_PORT 7878
#define BUFFSIZE 4096
#define LISTENQ 5

struct s s1;
struct s s1;

int acceptSocket(int socket,struct sockaddr *addr,socklen_t *addrlen);
int connectToServerByAddr(struct sockaddr_in servaddr);
int connectToServer(char *ip,unsigned short port);
int bindAndListenSocket(unsigned short port);
void splitCmd(char *buff, char **cmd,char **param);
unsigned short getPortFromFtpParam(char *param);
void getSockLocalIp(int fd,char *ipStr,int buffsize);
unsigned short getSockLocalPort(int sockfd);

int main(int argc, const char *argv[])
{
	int i;
	fd_set master_set, working_set;  //文件描述符集合
	struct timeval timeout;          //select 参数中的超时结构体
	int proxy_cmd_socket    = 0;     //proxy listen控制连接
	int accept_cmd_socket   = 0;     //proxy accept客户端请求的控制连接
	int connect_cmd_socket  = 0;     //proxy connect服务器建立控制连接
	int proxy_data_socket   = 0;     //proxy listen数据连接
	int accept_data_socket  = 0;     //proxy accept得到请求的数据连接（主动模式时accept得到服务器数据连接的请求，被动模式时accept得到客户端数据连接的请求）
	int connect_data_socket = 0;     //proxy connect建立数据连接 （主动模式时connect客户端建立数据连接，被动模式时connect服务器端建立数据连接）
	int selectResult = 0;     //select函数返回值
	int select_sd = 10;    //select 函数监听的最大文件描述符
	int pasv_mode = 1;

	char serverProxyIp[BUFFSIZE];    //待获得
	char clientProxyIp[BUFFSIZE];    //待获得 serverProxyIp和clientProxyIp可能不一样
	char serverIp[BUFFSIZE];

	unsigned short proxy_data_port;
	unsigned short data_port;
	socklen_t clilen;
	struct sockaddr_in cliaddr;

	if(argc != 2){
		printf("usage : proxy server_ip\n example: proxy 121.121.121.121\n");
	}
	strcpy(serverIp,argv[1]);


	FD_ZERO(&master_set);   //清空master_set集合
	bzero(&timeout, sizeof(timeout));

	proxy_cmd_socket = bindAndListenSocket(CMD_PORT);  //开启proxy_cmd_socket、bind（）、listen操作
	FD_SET(proxy_cmd_socket, &master_set);  //将proxy_cmd_socket加入master_set集合

	while (TRUE) {
		FD_ZERO(&working_set); //清空working_set文件描述符集合
		memcpy(&working_set, &master_set, sizeof(master_set)); //将master_set集合copy到working_set集合
		timeout.tv_sec = 60;    //Select的超时结束时间
		timeout.tv_usec = 0;    //ms

		//select循环监听 这里只对读操作的变化进行监听（working_set为监视读操作描述符所建立的集合）,第三和第四个参数的NULL代表不对写操作、和误操作进行监听
		selectResult = select(select_sd, &working_set, NULL, NULL, &timeout);

		// fail
		if (selectResult < 0) {
			perror("select() failed\n");
			exit(1);
		}

		// timeout
		if (selectResult == 0) {
			printf("select() timed out.\n");
			continue;
		}

		// selectResult > 0 时 开启循环判断有变化的文件描述符为哪个socket
		for (i = 0; i < select_sd; i++) {
			//判断变化的文件描述符是否存在于working_set集合
			if (FD_ISSET(i, &working_set)) {
				if (i == proxy_cmd_socket) {

					accept_cmd_socket = acceptSocket(proxy_cmd_socket,NULL,NULL);  //执行accept操作,建立proxy和客户端之间的控制连接
					connect_cmd_socket = connectToServer(serverIp,CMD_PORT); //执行connect操作,建立proxy和服务器端之间的控制连接

					getSockLocalIp(connect_cmd_socket,serverProxyIp,BUFFSIZE);            //获取本地ip，格式为port和pasv使用的格式
					getSockLocalIp(accept_cmd_socket,clientProxyIp,BUFFSIZE);            //获取本地ip，格式为port和pasv使用的格式
					printf("proxy ip from server's view : %s\n",serverProxyIp);
					printf("proxy ip from client's view : %s\n",clientProxyIp);

					//将新得到的socket加入到master_set结合中
					FD_SET(accept_cmd_socket, &master_set);
					FD_SET(connect_cmd_socket, &master_set);
				}

				if (i == accept_cmd_socket) {
					char buff[BUFFSIZE] = {0};
					char copy[BUFFSIZE] = {0};

					if (read(i, buff, BUFFSIZE) == 0) {
						close(i); //如果接收不到内容,则关闭Socket
						close(connect_cmd_socket);
						printf("client closed\n");

						//socket关闭后，使用FD_CLR将关闭的socket从master_set集合中移去,使得select函数不再监听关闭的socket
						FD_CLR(i, &master_set);
						FD_CLR(connect_cmd_socket, &master_set);

					} else {
						printf("command received from client : %s\n",buff);
						char *cmd,*param;
						strcpy(copy,buff);
						splitCmd(copy,&cmd,&param); 
						//如果接收到内容,则对内容进行必要的处理，之后发送给服务器端（写入connect_cmd_socket）

						//处理客户端发给proxy的request，部分命令需要进行处理，如PORT、RETR、STOR                        
						//PORT
						//////////////
						if(strcmp(cmd,"PORT") == 0){                //修改ip & port
							//在这儿应该让proxy_data_socket监听任意端口
							proxy_data_socket = bindAndListenSocket(0); //开启proxy_data_socket、bind（）、listen操作
							proxy_data_port = getSockLocalPort(proxy_data_socket);
							FD_SET(proxy_data_socket, &master_set);//将proxy_data_socket加入master_set集合
							pasv_mode = 0;
							data_port = getPortFromFtpParam(param);
							bzero(buff,BUFFSIZE);
							sprintf(buff,"PORT %s,%d,%d\r\n",serverProxyIp,proxy_data_port / 256,proxy_data_port % 256);
						}

						//写入proxy与server建立的cmd连接,除了PORT之外，直接转发buff内容
						printf("command sent to server : %s\n",buff);
						write(connect_cmd_socket, buff, strlen(buff));
					}
				}

				if (i == connect_cmd_socket) {
					//处理服务器端发给proxy的reply，写入accept_cmd_socket
					char buff[BUFFSIZE] = {0};
					if(read(i,buff,BUFFSIZE) == 0){
						close(i);
						close(accept_cmd_socket);
						FD_CLR(i,&master_set);
						FD_CLR(accept_cmd_socket,&master_set);
					}

					printf("reply received from server : %s\n",buff);
					//PASV收到的端口 227 （port）        
					//////////////
					if(buff[0] == '2' && buff[1] == '2' && buff[2] == '7'){
						proxy_data_socket = bindAndListenSocket(0); //开启proxy_data_socket、bind（）、listen操作
						proxy_data_port = getSockLocalPort(proxy_data_socket);
						FD_SET(proxy_data_socket, &master_set);//将proxy_data_socket加入master_set集合
						data_port = getPortFromFtpParam(buff + 27);
						bzero(buff + 27,BUFFSIZE - 27);
						sprintf(buff + 27,"%s,%d,%d).\r\n",clientProxyIp,proxy_data_port / 256,proxy_data_port % 256);
					}
					printf("reply sent to client : %s\n",buff);

					write(accept_cmd_socket,buff,strlen(buff));
				}

				if (i == proxy_data_socket) {
					if(pasv_mode){            //clinet connect
						accept_data_socket = acceptSocket(proxy_data_socket,NULL,NULL);        //client <-> proxy
						connect_data_socket = connectToServer(serverIp,data_port);        //proxy <-> server
					}
					else{    //主动模式
						accept_data_socket = acceptSocket(proxy_data_socket,NULL,NULL);        //proxy <-> server
						clilen = sizeof(cliaddr);
						if(getpeername(accept_cmd_socket,(struct sockaddr *)&cliaddr,&clilen) < 0){
							perror("getpeername() failed: ");
						}
						cliaddr.sin_port = htons(data_port);
						connect_data_socket = connectToServerByAddr(cliaddr);        //client <-> proxy
					}

					FD_SET(accept_data_socket, &master_set);
					FD_SET(connect_data_socket, &master_set);
					printf("data connectiong established\n");
					//建立data连接(accept_data_socket、connect_data_socket)
				}

				if (i == accept_data_socket) {

					int n;
					char buff[BUFFSIZE] = {0};
					if((n = read(accept_data_socket,buff,BUFFSIZE)) == 0){
						close(accept_data_socket);
						close(connect_data_socket);
						close(proxy_data_socket);
						FD_CLR(proxy_data_socket,&master_set);
						FD_CLR(accept_data_socket, &master_set);
						FD_CLR(connect_data_socket, &master_set);
					}
					else{
						write(connect_data_socket,buff,n);
					}


					//判断主被动和传输方式（上传、下载）决定如何传输数据
				}

				if (i == connect_data_socket) {
					int n;
					char buff[BUFFSIZE] = {0};
					if((n = read(connect_data_socket,buff,BUFFSIZE)) == 0){
						close(accept_data_socket);
						close(connect_data_socket);
						close(proxy_data_socket);
						FD_CLR(proxy_data_socket,&master_set);
						FD_CLR(accept_data_socket, &master_set);
						FD_CLR(connect_data_socket, &master_set);
					}
					else{
						write(accept_data_socket,buff,n);
					}
					//判断主被动和传输方式（上传、下载）决定如何传输数据
				}
			}
		}
	}

	return 0;
}

unsigned short getSockLocalPort(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t addrlen;
	addrlen = sizeof(addr);

	if(getsockname(sockfd,(struct sockaddr *)&addr,&addrlen) < 0){
		perror("getsockname() failed: ");
		exit(1);
	}

	return ntohs(addr.sin_port);
}


void getSockLocalIp(int fd,char *ipStr,int buffsize)
{

	bzero(ipStr,buffsize);

	struct sockaddr_in addr;
	socklen_t addrlen;
	addrlen = sizeof(addr);

	if(getsockname(fd,(struct sockaddr *)&addr,&addrlen) < 0){
		perror("getsockname() failed: ");
		exit(1);
	}

	inet_ntop(AF_INET,&addr.sin_addr,ipStr,addrlen);

	char *p = ipStr;
	while(*p){
		if(*p == '.') *p = ',';
		p++;
	}
}

unsigned short getPortFromFtpParam(char *param)
{
	unsigned short port,t;
	int count = 0;
	char *p = param;    

	while(count < 4){
		if(*(p++) == ','){
			count++;
		}
	}

	sscanf(p,"%hu",&port);
	while(*p != ',' && *p != '\r' && *p != ')') p++;
	if(*p == ','){
		p++;
		sscanf(p,"%hu",&t);
		port = port * 256 + t;
	}

	return port;
}

//从FTP命令行中解析出命令和参数
void splitCmd(char *buff, char **cmd,char **param)
{
	int i;
	char *p;

	while((p = &buff[strlen(buff) - 1]) && (*p == '\r' || *p == '\n')) *p = 0;

	p = strchr(buff,' ');
	*cmd = buff;

	if(!p){
		*param = NULL;
	}else{
		*p = 0;
		*param = p + 1;
	}

	for(i = 0;i < strlen(*cmd);i++){
		(*cmd)[i] = toupper((*cmd)[i]);
	}
}


int acceptSocket(int cmd_socket,struct sockaddr *addr,socklen_t *addrlen)
{
	int fd = accept(cmd_socket,addr,addrlen);
	if(fd < 1){
		perror("accept() failed:");
		exit(1);
	}

	return fd;
}


int connectToServerByAddr(struct sockaddr_in servaddr)
{
	int fd;

	struct sockaddr_in cliaddr;
	bzero(&cliaddr,sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);    
	//cliaddr.sin_port = htons(20);

	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0){
		perror("socket() failed :");
		exit(1);
	}

	if(bind(fd,(struct sockaddr *)&cliaddr,sizeof(cliaddr) ) < 0){
		perror("bind() failed :");
		exit(1);
	}

	servaddr.sin_family = AF_INET;
	if(connect(fd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
		perror("connect() failed :");
		exit(1);
	}

	return fd;
}


int connectToServer(char *ip,unsigned short port)
{
	int fd;
	struct sockaddr_in servaddr;

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_pton(AF_INET,ip,&servaddr.sin_addr);

	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0){
		perror("socket() failed :");
		exit(1);
	}

	if(connect(fd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
		perror("connect() failed :");
		exit(1);
	}

	return fd;
}

int bindAndListenSocket(unsigned short port)
{
	int fd;
	struct sockaddr_in addr;

	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0){
		perror("socket() failed: ");
		exit(1);
	}

	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	if(bind(fd,(struct sockaddr*)&addr,sizeof(addr)) < 0){
		perror("bind() failed: ");
		exit(1);
	}

	if(listen(fd,LISTENQ) < 0){
		perror("listen() failed: ");
		exit(1);
	}

	return fd;
}
