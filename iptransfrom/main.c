#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	in_addr_t ip;
	struct in_addr ip2;
	char *ipstr = NULL;

	//下面两句等价
	ip = inet_addr("192.168.31.1");
	ip = htonl(inet_network("192.168.31.1"));

	inet_aton("192.168.31.1", &ip2);
	inet_pton(AF_INET, "192.168.31.1", &ip2);

	ipstr = inet_ntoa(ip2);
	printf("%s\n", ipstr);

	inet_ntop(AF_INET, &ip2, ipstr, 32);
	printf("%s\n", ipstr);
	
	return 0;
}
