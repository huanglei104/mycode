#include <iniparser.h>
#include <stdbool.h>
#include <glib.h>
#include <http_parser.h>

struct {
	int port;
	int timeout;
	int connections;
	char webroot[128];
} config = {
	8888, 60, 1024, "aaa"
};

bool parser_section(dictionary *dic, const char *section)
{
	int n, value;
	const char *keys[64];

	n = iniparser_getsecnkeys(dic, section);
	if (n <= 0) return false;

	if (iniparser_getseckeys(dic, section, keys) == NULL) {
		return false;
	}

	for (int i = 0; i < n; i++) {
		if (strcmp("core:port", keys[i]) == 0) {
			value = iniparser_getint(dic, keys[i], -1);
			config.port = value != -1 ? value : config.port;

		} else if (strcmp("core:timeout", keys[i]) == 0) {
			value = iniparser_getint(dic, keys[i], -1);
			config.timeout = value != -1 ? value : config.timeout;

		} else if (strcmp("core:connections", keys[i]) == 0) {
			value = iniparser_getint(dic, keys[i], -1);
			config.connections = value != -1 ? value : config.connections;
		}
	}
	return true;
}

bool config_init()
{
	dictionary *dic;

	dic = iniparser_load("./config.ini");
	if (dic == NULL) return false;

	parser_section(dic, "core");
	parser_section(dic, "web");

	return true;
}
