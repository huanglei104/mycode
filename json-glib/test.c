#include <stdio.h>
#include <json-glib/json-glib.h>


GHashTable *ftp_table, *mail_table;

void foreach(JsonObject *obj, const gchar *name, JsonNode *node, gpointer data)
{
	JsonObject *child;
	JsonArray *array;
	const char *str, *type;

	type = json_node_type_name(node);


	if (strcmp(type, "JsonObject") == 0) {
		child = json_node_get_object(node);
		json_object_foreach_member(child, foreach, NULL);

	} else if (strcmp(type, "JsonArray") == 0) {
		array = json_object_get_array_member(obj, name);

		for (int i = 0; i < json_array_get_length(array); i++) {
			node = json_array_get_element(array, i);
			str = json_node_get_string(node);
			printf("   *%s ", str);
		}
	}


	printf("\n");
}

int main(int argc, char *argv[])
{
	gboolean ret;
	JsonParser *parser;
	JsonNode *node;
	JsonObject *obj;


	parser = json_parser_new();

	ret = json_parser_load_from_file(parser, "/etc/jsac/filter.json", NULL);
	if (ret == FALSE) {
		printf("error\n");
	}

	node = json_parser_get_root(parser);

	obj = json_node_get_object(node);
	json_object_foreach_member(obj, foreach, NULL);

	return 0;
}
