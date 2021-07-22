#include "gmime/gmime-message.h"
#include <stdio.h>
#include <fcntl.h>
#include <gmime/gmime.h>

void  ff(GMimeObject *parent, GMimeObject *part, gpointer user_data) {
	printf("part id %s\n", part->content_id);
	printf("part type %s\n", part->content_type->type);
	printf("part subtype %s\n", part->content_type->subtype);
}
void mfoo(GMimeObject *parent, GMimeObject *part, gpointer user_data) {

	int *count = user_data;

	(*count)++;
}

int main(int argc, char *argv[]) {
	
	int msg_part_count = 0;

	g_mime_init(0);
	GMimeStream *stream = g_mime_stream_file_new_for_path("/home/huanglei/Downloads/textandtxt.txt", "r");
	GMimeParser *parse = g_mime_parser_new_with_stream(stream);
	GMimeMessage *message = g_mime_parser_construct_message(parse);
	g_mime_message_foreach(message, mfoo, &msg_part_count);
	return 0;
	GMimeObject *part = g_mime_message_get_mime_part(message);
	GMimeObject *body = g_mime_message_get_body(message);
	const char *mid = g_mime_message_get_message_id(message);
	//g_mime_content_type_to_string();
	char *bodyStr = g_mime_object_to_string(body);
	char *partStr = g_mime_object_to_string(part);
	//printf("message id: %s\n", mid);
	//printf("body:\n%s\n", bodyStr);

	if(GMIME_IS_MULTIPART(part)) {
		int count;
		GMimeMultipart *multipart;
		g_mime_multipart_encrypted_new();
		multipart = GMIME_MULTIPART(part);
		const char *multipartStr = g_mime_object_to_string((GMimeObject*)multipart);
		printf("multipartStr:\n%s---\n", multipart->preface);
		printf("partStr:\n%s---\n", partStr);
		printf("preface %s", multipart->preface);
		printf("boundary %s", multipart->boundary);
		count = g_mime_multipart_get_count(multipart);
		printf("mail is multipart, count is %d\n", count);
		g_mime_multipart_foreach(multipart, ff, NULL);
	} else {
		printf("mail is not multipart\n");
	}
	//GMimePart * part = GMIME_PART(partObj);

	//if(g_mime_part_is_attachment((GMimePart*)part)) {
		//printf("have appachment\n");
	//}
	const char *subject = g_mime_message_get_subject(message);
	const char *from = g_mime_message_get_sender(message);
	const char *replyto = g_mime_message_get_reply_to(message);
	const char *obj = g_mime_object_to_string((GMimeObject*)message);

	GMimeContentType *type = part->content_type;
	char *header = g_mime_object_get_headers((GMimeObject*)message);
	//printf("from:%s\n", from);
	//printf("replyto:%s\n", replyto);
	//printf("subject:%s\n", subject);
	//printf("type:%s\n", type->type);
	//printf("obj:\n%s\n", obj);
	//printf("header:\n%s\n", header);
	//printf("part:\n%s\n", partStr);
	return 0;
}
