#include <netinet/in.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/epoll.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <iniparser.h>
#include <dictionary.h>
#include <glib.h>
#include <http_parser.h>


struct connection_s;
struct buffer_s;

typedef struct connection_s connection_t;
typedef struct buffer_s buffer_t;
typedef int (*handler_t)(connection_t*);

int event_handler(connection_t *c);

struct buffer_s {
	char *start;
	char *pos;
	char *last;
	char *end;
};

struct connection_s {
	int fd;
	buffer_t *buf;
	handler_t handler;
};

struct {
	int port;
	int efd;
	int timeout;
	int connections;
	GPtrArray *conns;
	http_parser *parser;
	http_parser_settings settings;
} global = {
	8888, -1, 60, 1024, NULL, NULL
};


buffer_t* alloc_buffer(connection_t *c, int size)
{
	buffer_t *buf;

	buf = malloc(sizeof(buffer_t));
	buf->start = malloc(size);
	buf->end = buf->start + size - 1;
	buf->pos = buf->start;
	buf->last = buf->pos;

	return buf;
}

connection_t* get_connection(int fd)
{
	int i;
	connection_t *c;

	for (i = 0; i < global.connections; i++) {
		c = g_ptr_array_index(global.conns, i);
		if (c->fd == -1) {
			return c;
		}
	}

	return NULL;
}

int add_connection(connection_t *c)
{
	int ret;
	struct epoll_event ee;

	ee.events = EPOLLIN | EPOLLET;
	ee.data.ptr = c;

	ret = epoll_ctl(global.efd, EPOLL_CTL_ADD, c->fd, &ee);
	if (ret == -1)
		return perror("epoll_ctl"), -1;

	return ret;
}

int event_accept(connection_t *c)
{
	int ret;
	int sockfd;
	connection_t *newc;

	sockfd = accept(c->fd, NULL, NULL);
	if(sockfd == -1) {
		perror("accept");
		return -1;
	}

	newc = get_connection(sockfd);
	newc->fd = sockfd;
	newc->handler = event_handler;

	ret = add_connection(newc);
	if (ret == -1) return -1;

	return 0;
}

void close_connection(connection_t *c)
{
	close(c->fd);
	c->fd = -1;
}

int message_begin(http_parser *_)
{
	printf("%s\n", __func__);
	return 0;
}

int message_complete(http_parser *_)
{
	printf("%s\n", __func__);
	return 0;
}

int chunk_header(http_parser *_)
{
	printf("%s\n", __func__);
	return 0;
}

int header_field(http_parser* _, const char *at, size_t length)
{
	printf("%s\n", __func__);
	printf("%s\n", at);
	return 0;
}

int url(http_parser* _, const char *at, size_t length)
{
	if (strncasecmp(at, "/", length) == 0) {
		printf("home page\n");
	}

	return 0;
}

int event_handler(connection_t *c)
{
	int n;
	int remain;
	buffer_t *buf;

	buf = c->buf;

	remain = buf->end - buf->last;

	while (1) {
		n = recv(c->fd, buf->last, remain, MSG_DONTWAIT);
		if (n == 0) {
			printf("connection closed\n");
			break;
		} else if (n < 0){
			if (errno == EAGAIN)
				break;
			else {
				perror("recv");
				close_connection(c);
				return -1;
			}
		}
		buf->last += n;
	}

	http_parser_execute(global.parser, &global.settings, buf->pos,
			buf->last - buf->pos);
	if (global.parser->http_errno)
		return printf("http parser errno\n"), false;

	return true;
}


int listening_init()
{
	int ret;
	int sockfd;
	int opt = 1;
	struct sockaddr_in addr;
	struct epoll_event ee;
	connection_t *c;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(global.port);

	global.efd = epoll_create(20);
	if (global.efd == -1) {
		perror("epoll_create");
		return -1;
	}

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) return errno;

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
		perror("setsocktopt");
		return -1;
	}

	ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1) {
		perror("bind");
		return -1;
	}

	if (listen(sockfd, 10) == -1) {
		perror("listen");
		return -1;
	}

	c = malloc(sizeof(connection_t));
	c->fd = sockfd;
	c->handler = event_accept;
	c->buf = NULL;

	ee.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
	ee.data.ptr = c;

	if (epoll_ctl(global.efd, EPOLL_CTL_ADD, sockfd, &ee) == -1) {
		perror("epoll_ctl ADD");
		return -1;
	}

	return 0;
}

void timeout_handler()
{
	int i;
	connection_t *c;

	for (i = 0; i < global.connections; i++) {
		c = g_ptr_array_index(global.conns, i);
		if (c->fd != -1) {
			close_connection(c);
		}
	}
}

int wait_event()
{
	int i, ret;
	struct epoll_event events[20];

	bzero(events, sizeof(events));

	while(1) {
		ret = epoll_wait(global.efd, events, 20, global.timeout * 1000);
		if(ret == 0) {
			timeout_handler();
		}

		for(i = 0; i < ret; i++) {
			connection_t *c = events[i].data.ptr;
			c->handler(c);
		}
	}

	return 0;
}

bool init_connections()
{
	int i;
	connection_t *c;

	global.conns = g_ptr_array_new();
	if (global.conns == NULL) {
		printf("internal error\n");
		return false;
	}

	for (i = 0; i < global.connections; i++) {
		c = malloc(sizeof(connection_t));
		if (c == NULL) {
			perror("malloc");
			return false;
		}
		c->fd = -1;
		c->handler = NULL;
		c->buf = alloc_buffer(c, 16384);
		g_ptr_array_add(global.conns, c);
	}

	return true;
}

bool config_init()
{
	int n;
	int value;
	const char *keys[64];
	dictionary *dic;

	dic = iniparser_load("./config.ini");
	if (dic == NULL) return false;

	n = iniparser_getsecnkeys(dic, "core");
	if (n <= 0) return false;

	if (iniparser_getseckeys(dic, "core", keys) == NULL) {
		return false;
	}

	for (int i = 0; i < n; i++) {
		if (strcmp("core:port", keys[i]) == 0) {
			value = iniparser_getint(dic, keys[i], -1);
			global.port = value != -1 ? value : global.port;

		} else if (strcmp("core:timeout", keys[i]) == 0) {
			value = iniparser_getint(dic, keys[i], -1);
			global.timeout = value != -1 ? value : global.timeout;

		} else if (strcmp("core:connections", keys[i]) == 0) {
			value = iniparser_getint(dic, keys[i], -1);
			global.connections = value != -1 ? value : global.connections;
		}
	}

	return true;
}

bool global_init()
{
	global.parser = malloc(sizeof(http_parser));
	if (global.parser == NULL) {
		perror("malloc");
		return false;
	}

	global.settings.on_message_begin = message_begin;
	global.settings.on_message_complete = message_complete;
	global.settings.on_url = url;
	global.settings.on_chunk_header = chunk_header;
	global.settings.on_header_field = header_field;

	http_parser_init(global.parser, HTTP_REQUEST);

	return true;
}

int main(int argc, char *argv[])
{
	if (global_init() == false)
		return -1;

	if (config_init() == false)
		printf("using default configuration\n");

	if (init_connections() == false)
		return -1;

	if (listening_init() == -1)
		return -1;

	if (wait_event() == -1)
		return -1;

	return 0;
}
