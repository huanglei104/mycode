#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

const char *inet_ntop2(int __af, const void *__restrict __cp,
		char *__restrict __buf, socklen_t __len)
{
	if (__af == AF_INET) {
		struct sockaddr_in *addr = (struct sockaddr_in*)__cp;
		return inet_ntop(__af, &addr->sin_addr, __buf, __len);

	} else if (__af == AF_INET6) {
		struct sockaddr_in6 *addr = (struct sockaddr_in6*)__cp;
		return inet_ntop(__af, &addr->sin6_addr, __buf, __len);
	}

	return NULL;
}

