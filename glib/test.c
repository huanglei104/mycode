#include <stdio.h>
#include <glib.h>
#include <string.h>
#include <glib-object.h>


void glist_test() {

	int length;
	GList *list;

	list = g_list_append(list, "hello");
	list = g_list_append(list, "world");
	length = g_list_length(list);
	printf("%d\n", length);
}

int main(int argc, char *argv[])
{
	glist_test();
	return 0;
}
