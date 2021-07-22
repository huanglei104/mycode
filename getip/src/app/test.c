#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <ifaddrs.h>
#include <string.h>

#include <common.h>

static void getip1()
{
	int		family;
	struct	ifaddrs *addrs, *addr;

	char	ip[INET6_ADDRSTRLEN] = {0};

	if (getifaddrs(&addrs) == -1) {
		perror("getifaddrs");
		return;
	}

	for (addr = addrs ; addr; addr = addr->ifa_next) {
		if (addr->ifa_addr == NULL) continue;

		family = addr->ifa_addr->sa_family;
		if (family != AF_INET && family != AF_INET6)
			continue;

		if (inet_ntop2(family, addr->ifa_addr, ip, INET6_ADDRSTRLEN) == NULL) {
			perror("inet_ntop");
			return;
		}

		if (family == AF_INET)
			printf("interface:%s\naddress4:%s\n\n", addr->ifa_name, ip);

		else
			printf("interface:%s\naddress6:%s\n\n", addr->ifa_name, ip);
	}

	freeifaddrs(addrs);
}

static void getip2()
{
	int MAXINTERFACES = 16;
	int fd, intrface;
	char *ip = NULL;
	struct ifreq buf[MAXINTERFACES];
	struct ifconf ifc;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) return perror("socket");

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = (caddr_t)buf;

	if (ioctl(fd, SIOCGIFCONF, &ifc) == -1)
		return perror("ioctl");

	intrface = ifc.ifc_len / sizeof(struct ifreq);

	while (intrface-- > 0) {
		if ((ioctl(fd, SIOCGIFADDR, &buf[intrface])) == -1) {
			perror("ioctl");
			break;
		}

		ip = inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr);
		printf("interface:%s\naddress4:%s\n", buf[intrface].ifr_name, ip);
	}

	fd = socket(AF_INET6, SOCK_STREAM, 0);
	if (fd == -1) return perror("socket");

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = (caddr_t)buf;

	if (ioctl(fd, SIOCGIFCONF, &ifc) == -1)
		return perror("ioctl");

	intrface = ifc.ifc_len / sizeof(struct ifreq);

	while (intrface-- > 0) {
		if ((ioctl(fd, SIOCGIFADDR, &buf[intrface])) == -1) {
			perror("ioctl");
			break;
		}

		ip = inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr);
		printf("interface:%s\naddress6:%s\n", buf[intrface].ifr_name, ip);
	}

	close(fd);
}

void* run(void *args)
{
	return NULL;
}

int main(int argc, char *argv[])
{
	getip1();
	getip2();

	return 0;
}
