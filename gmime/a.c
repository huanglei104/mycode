#include <stdio.h>
#include <stdbool.h>
#include <gmime/gmime.h>

void Walk(GMimeObject* pPart,int nDepth){
	printf("Geting %d part content type...\n",nDepth);
	GMimeContentType* pContentType = g_mime_object_get_content_type(pPart) ;
	char* szContentType = g_mime_content_type_to_string(pContentType);
	printf("The content type is: %s or direct get from the object(%s/%s)\n",szContentType,pContentType->type,pContentType->subtype);
	g_free(szContentType);
	char* szObject = g_mime_object_to_string(pPart);
	//      printf("The object is :%s\n",szObject);
	g_free(szObject);
	const char* szHeader = g_mime_object_get_headers(pPart);
	printf("The object's header is:%s\n",szHeader);
	const char* szContentId = g_mime_object_get_content_id (pPart);
	printf("The object's content id is:%s\n",szContentId);
	if(GMIME_IS_MULTIPART(pPart)) {
		GMimeMultipart* pMultipart = GMIME_MULTIPART(pPart);
		printf("The GMimeObject can convert to GMimeMultiPart object...\n");
		printf("The multipart preface is: %s\n",g_mime_multipart_get_preface(GMIME_MULTIPART(pPart)));
		//printf("The multipart number is %d\n", g_mime_multipart_get_number(pMultipart));
		printf("The multipart boundary is:%s\n",g_mime_multipart_get_boundary (pMultipart));
		GPtrArray *child = pMultipart->children;
		//GList* pSubParts =  pMultipart->subparts;
		if(pSubParts==NULL)
			printf("The multipart has no subparts, wrong mail????\n");
		int j=0;
		while(pSubParts) {
			pSubParts = pSubParts->next;
			printf("multi part no%d\n",j++);
		}
	}
}

void Analyze(GMimeMessage* pMessage) {
	printf("analyze the message begin...\n");
	Walk(pMessage->mime_part,0);
}

int main(int argc,char** argv) {
	g_mime_init(0);
	if(argc<2) {
		printf("error open file to parser. hello <file>\n");
		return 0;
	}
	printf("hello, gmime! please\n");
	FILE* fp = fopen(argv[1],"rb");
	GMimeStream* pStream = g_mime_stream_file_new(fp);
	printf("[main] g_mime_stream_file_new success!\n");
	GMimeFilter* pCrlfFilter = g_mime_filter_crlf_new (GMIME_FILTER_CRLF_DECODE,GMIME_FILTER_CRLF_MODE_CRLF_ONLY);

	printf("[main] new crlf filter success!\n");



	GMimeStream* pFilterStream = g_mime_stream_filter_new_with_stream (pStream);

	printf("[main] create filter stream with file stream success!\n");

	printf("unref the stream object.\n");

	g_mime_stream_unref(pStream);

	g_mime_stream_filter_add (GMIME_STREAM_FILTER (pFilterStream), pCrlfFilter);

	g_object_unref (pCrlfFilter);

	printf("[main] add crlf filter to decode success!\n");



	GMimeParser* pParser = g_mime_parser_new();
	if(!pParser) {
		printf("error new parser.\n");
	}
	printf("new parser success!\n");
	g_mime_parser_init_with_stream(pParser,pFilterStream);
	GMimeMessage* pMessage = g_mime_parser_construct_message(pParser);
	if(!pMessage) {
		printf("error construct the message!\n");
		return 0;
	}
	printf("construct message with filter stream success!\n");
	printf("unref the filter stream.\n");
	g_mime_stream_unref(pFilterStream);
	printf("unref the parser object.\n");
	g_object_unref(pParser);
	printf("sender:%s\n",g_mime_message_get_sender(pMessage));
	printf("rcpt to:%s\n",g_mime_message_get_reply_to (pMessage));
	printf("subject:%s\n",g_mime_message_get_subject (pMessage));
	gboolean is_html;
	printf("body:%s\n",g_mime_message_get_body(pMessage,true,&is_html));
	Analyze(pMessage);
	printf("unref the pMessage object.\n");
	g_object_unref(GMIME_OBJECT(pMessage));
	return 1;
}
