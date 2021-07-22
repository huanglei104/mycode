#include <netdb.h>
#include <arpa/inet.h>
#include <openssl/asn1.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <http_parser.h>
#include <glib.h>
#include <gumbo.h>
#include <wchar.h>

#define BUFSIZE 10240
#define HOST "github.com"
#define RESOURCE "/Alvin9999/new-pac/wiki/ss%E5%85%8D%E8%B4%B9%E8%B4%A6%E5%8F%B7"
#define URL "GET " RESOURCE " HTTP/1.1\r\nHost: " HOST "\r\nConnection: close\r\n\r\n"
#define CONFIG \
"{\n" \
"    \"server\":\"%s\",\n" \
"    \"server_port\":%s,\n" \
"    \"local_address\": \"127.0.0.1\",\n" \
"    \"local_port\":1080,\n" \
"    \"password\":\"%s\",\n" \
"    \"timeout\":300,\n" \
"    \"method\":\"%s\",\n" \
"    \"fast_open\": false,\n" \
"    \"workers\": 1,\n" \
"    \"prefer_ipv6\": false\n" \
"}\n"

typedef struct {
	char region[16];
	char ip[16];
	char port[8];
	char password[64];
	char method[16];
	char protocol[32];
	char garble[16];
} ss_info_t;

int g_argc;
char **g_argv;

unsigned char* ascii_cpy(unsigned char *dst, unsigned char *src) {

	while (*src) {
		*dst++ = *src++;
	}

	return dst;
}

unsigned char* ascii_chr(unsigned char *src, unsigned char c) {
	while (*src) {
		if (*src == c) return src;
		src++;
	}
	return NULL;
}

GumboNode* find_tag(GumboNode *parent, GumboTag tag, GumboAttribute *attr)
{
	int i;
	GumboAttribute *at;
	GumboNode *node;
	GumboVector *children;

	children = &parent->v.element.children;

	for (i = 0; i < children->length; i++) {
		node = children->data[i];
		if (node->type != GUMBO_NODE_ELEMENT) continue;
		if (node->v.element.tag != tag) continue;
		if (attr) {
			at = gumbo_get_attribute(&node->v.element.attributes, attr->name);
			if (at && strcmp(at->value, attr->value) == 0) {
				return node;
			}
			continue;
		}
		return node;
	}

	return NULL;
}

void replace_nbsp(ss_info_t *info)
{
	char *p;

	p = strstr(info->password, " ");

	if (p) {
		memmove(p + 1, p + 2, strlen(p + 2));
		*p = 32;
	}
}

GPtrArray* getssinfo(GumboNode *tbody)
{
	int i, j, index;
	const char *text;
	GumboNode *tr, *td, *tnode;
	GumboVector *tds;
	GumboVector *trs = &tbody->v.element.children;
	GPtrArray *array = g_ptr_array_new();

	for (i = 0; i < trs->length; i++) {
		tr= trs->data[i];
		if (tr->type != GUMBO_NODE_ELEMENT) continue;
		if (tr->v.element.tag != GUMBO_TAG_TR) continue;
		tds = &tr->v.element.children;
		ss_info_t *info = calloc(1, sizeof(ss_info_t));
		index = -1;
		for (j = 0; j < tds->length; j++) {
			td = tds->data[j];
			if (td->type != GUMBO_NODE_ELEMENT) continue;
			if (td->v.element.tag != GUMBO_TAG_TD) continue;
			index++;
			tnode = (GumboNode*)td->v.element.children.data[0];
			if (tnode == NULL) continue;
			text = tnode->v.text.text;
			if (text == NULL) continue;
			if (index == 0 && tnode) strcpy(info->region, text);
			if (index == 1 && tnode) strcpy(info->ip, text);
			if (index == 2 && tnode) strcpy(info->port, text);
			if (index == 3 && tnode) strcpy(info->password, text);
			if (index == 4 && tnode) strcpy(info->method, text);
			if (index == 5 && tnode) strcpy(info->protocol, text);
			if (index == 6 && tnode) strcpy(info->garble, text);
		}
		replace_nbsp(info);
		g_ptr_array_add(array, info);
	}
	return array;
}

int on_message_complete(http_parser* _)
{
	int index;
	FILE *fp;
	GumboNode *parent;
	GPtrArray *array;
	GumboOutput *output;
	GumboAttribute *attr;

	output = gumbo_parse(((GString*)_->data)->str);
	attr = malloc(sizeof(GumboAttribute));
	parent = output->root;

	parent = find_tag(parent, GUMBO_TAG_BODY, NULL);
	if (parent == NULL) return printf("BODY NULL\n");

	attr->name = "class";
	attr->value = "application-main ";
	parent = find_tag(parent, GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV 1 NULL\n");

	attr->name = "itemtype";
	attr->value = "http://schema.org/SoftwareSourceCode";
	parent = find_tag(parent , GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV 2 NULL\n");

	parent = find_tag(parent, GUMBO_TAG_MAIN, NULL);
	if (parent == NULL) return printf("MAIN NULL\n");

	attr->name = "class";
	attr->value = "container-xl clearfix new-discussion-timeline px-3 px-md-4 px-lg-5";
	parent = find_tag(parent, GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV3 NULL\n");

	attr->name = "class";
	attr->value = "repository-content ";
	parent = find_tag(parent, GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV4 NULL\n");

	attr->name = "id";
	attr->value = "wiki-wrapper";
	parent = find_tag(parent, GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV5 NULL\n");

	attr->name = "id";
	attr->value = "wiki-content";
	parent = find_tag(parent, GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV6 NULL\n");

	attr->name = "class";
	attr->value = "gutter-condensed gutter-lg flex-column flex-md-row d-flex";
	parent = find_tag(parent, GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV7 NULL\n");

	attr->name = "class";
	attr->value = "flex-shrink-0 col-12 col-md-9 mb-4 mb-md-0";
	parent = find_tag(parent, GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV8 NULL\n");

	attr->name = "id";
	attr->value = "wiki-body";
	parent = find_tag(parent, GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV9 NULL\n");

	attr->name = "class";
	attr->value = "markdown-body";
	parent = find_tag(parent, GUMBO_TAG_DIV, attr);
	if (parent == NULL) return printf("DIV10 NULL\n");

	parent = find_tag(parent, GUMBO_TAG_TABLE, NULL);
	if (parent == NULL) return printf("TABLE NULL\n");

	parent = find_tag(parent, GUMBO_TAG_TBODY, NULL);
	if (parent == NULL) return printf("TABLE-BODY NULL\n");

	free(attr);

	array = getssinfo(parent);

	fp = fopen("/etc/shadowsocks/github.json", "w+");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}

	for (index = 0; index < array->len; index++) {
		ss_info_t *info = g_ptr_array_index(array, index);
		printf("%d %s %s %s %s %s\n", index + 1, info->region, info->ip, info->port, info->password, info->method);
	}

	if (g_argc <= 1) index = 1;
	else {
		index = atoi(g_argv[1]);
		if (index <= 0) index = 1;
		if (index > array->len) index = array->len;
	}

	ss_info_t *info = g_ptr_array_index(array, index - 1);
	fprintf(fp, CONFIG, info->ip, info->port, info->password, info->method);
	printf("select %d\n", index);
	fclose(fp);

	g_ptr_array_free(array, TRUE);
	g_string_free(_->data, TRUE);

	gumbo_destroy_output(&kGumboDefaultOptions, output);

	return 0;
}

int on_headers_complete(http_parser* _)
{
	return _->data = g_string_new(""), 0;
}

int on_body(http_parser* _, const char* at, size_t length)
{
	return g_string_append_len(_->data, at, length), 0;
}

int main(int argc, char *argv[])
{
	printf("%c\n", 160);
	int	ret;
	int sockfd;
	SSL *ssl;
	char res_buf[BUFSIZE] = {0};
	const SSL_METHOD *method;
	struct addrinfo *info;
	SSL_CTX *ctx;
	http_parser *parser;
	http_parser_settings parser_set;

	g_argc = argc;
	g_argv = argv;
	parser_set.on_body = on_body;
	parser_set.on_headers_complete = on_headers_complete;
	parser_set.on_message_complete = on_message_complete;

	SSL_library_init();
	ERR_load_crypto_strings();
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();

	method = SSLv23_client_method();
	if (method == NULL) {
		printf("SSLv23_client_method failed:");
		ERR_print_errors_fp(stdin);
		return -1;
	}
	ctx = SSL_CTX_new(method);
	if (ctx == NULL) {
		printf("SSL_CTX_new failed:");
		ERR_print_errors_fp(stdin);
		return -1;
	}

	ssl = SSL_new(ctx);
	if (ssl == NULL) {
		printf("SSL_new failed:");
		ERR_print_errors_fp(stdin);
		return -1;
	}

	if (getaddrinfo(HOST, "https", NULL, &info) != 0) {
		perror("getaddrinfo");
		return -1;
	}

	sockfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if(sockfd == -1) {
		perror("socket");
		return -1;
	}

	if (connect(sockfd, info->ai_addr, info->ai_addrlen) == -1) {
		perror("connect");
		return -1;
	}

	printf("TCP connected\n");

	if (SSL_set_fd(ssl, sockfd) == 0) {
		printf("SSL_set_fd failed:");
		ERR_print_errors_fp(stdin);
		return -1;
	}

	if (SSL_connect(ssl) != 1) {
		printf("SSL_connect failed:");
		ERR_print_errors_fp(stdin);
		return -1;
	}

	printf("SSL connected\n");

	parser = malloc(sizeof(http_parser));
	if (parser == NULL) {
		perror("malloc");
		return -1;
	}
	http_parser_init(parser, HTTP_RESPONSE);

	if (SSL_write(ssl, URL, sizeof(URL) - 1) == 0) {
		printf("SSL_write failed:");
		ERR_print_errors_fp(stdin);
		return -1;
	}

	for (;;) {
		if ((ret = SSL_read(ssl, res_buf, BUFSIZE)) == 0) {
			if (SSL_get_error(ssl, ret) == SSL_ERROR_ZERO_RETURN)
				break;
			return printf("SSL_read failed\n"), -1;
		}

		http_parser_execute(parser, &parser_set, res_buf, ret);
		if (parser->http_errno)
			return printf("http_parser_execute error\n");
	}

	free(parser);
	SSL_CTX_free(ctx);
	SSL_free(ssl);

	return 0;
}
