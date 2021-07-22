#include "arraylist.h"
#include "json_object.h"
#include <stdio.h>
#include <json.h>
#include <string.h>

static int _(json_object *jso)
{
	struct json_object_iterator iterator, iter_end;

	iterator = json_object_iter_begin(jso);
	iter_end = json_object_iter_end(jso);

	while (!json_object_iter_equal(&iterator, &iter_end)) {

		printf("...%s\n", json_object_iter_peek_name(&iterator));

		json_object *value = json_object_iter_peek_value(&iterator);
		if (json_object_get_type(value) != json_type_array) {

			printf(" invalid configuration\n");
			break;

		} else {

			array_list *list = json_object_get_array(value);
			for (int i = 0; i < list->length; i++) {
				json_object *obj = array_list_get_idx(list, i);

				const char *s = json_object_to_json_string_ext(obj,
						JSON_C_TO_STRING_PRETTY);
				printf("-%s\n", s);
			}


			printf("\n");
		}

		json_object_iter_next(&iterator);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	struct json_object *jso, *ftp, *mail;

	jso = json_object_from_file("/etc/jsac/filter.json");
	if (jso == NULL) {
		printf("parse json failed\n");
		return 0;
	}

	ftp = json_object_object_get(jso, "ftp");
	mail = json_object_object_get(jso, "mail");
	if (!(ftp || mail)) {
		printf("ftp error\n");
		return 0;
	}

	_(ftp);
	_(mail);
	return 0;
}
