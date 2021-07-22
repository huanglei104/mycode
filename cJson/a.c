#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "cJSON.h"


void parse(cJSON *json, int level) {

	char *prefix;
	if(json == NULL) {
		return;
	}

	if(level == 1) {
		prefix = "protocol";
	} else {
		prefix = "  ";
	}
	printf("%s:%s\n", prefix, json->string);
	if(cJSON_IsObject(json)) {
		parse(json->child, level + 1);
	} else if(cJSON_IsArray(json)) {
		int size = cJSON_GetArraySize(json);
		int index;
		for(index = 0; index < size; index++) {
			char *value =cJSON_GetStringValue(cJSON_GetArrayItem(json, index));
			printf("----%s\n", value);
		}
		printf("%d\n", cJSON_GetArraySize(json));
	}
	parse(json->next, level);
}

int main(int argc, char *argv[]) {

	char* protocol[] = {"ftp", "mail", NULL};
	char* element[] = {"allow", "mail", NULL};

	char buf[1024] = {0};

	int file = open("/etc/jsac/filter.json", O_RDONLY);
	read(file, buf, 1024);

	cJSON *json = cJSON_Parse(buf);
	parse(json->child, 1);

	return 0;
}
