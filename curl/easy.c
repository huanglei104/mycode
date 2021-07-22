#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>
#include <stdlib.h>

//#define CURL_DEBUG 1
#define CURL_WAIT_TIMEOUT_MSECS 60000 //60s
#define CURL_MULIT_MAX_NUM 5

static size_t recive_data_fun( void *ptr, size_t size, size_t nmemb, void *stream){
	return fwrite(ptr,size,nmemb,(FILE*)stream);
}

static size_t read_head_fun( void *ptr, size_t size, size_t nmemb, void *stream){
	char head[2048] = {0};
	memcpy(head,ptr,size*nmemb+1);
	printf(" %s \n",head);
	return size*nmemb;
}

int main(int argc, char **argv)
{
	if(argc < 3){
		printf("arg1 is url; arg2 is out file\n");
		return -1;
	}
	char* url = strdup(argv[1]);
	char* filename= strdup(argv[2]);
	CURL* curl_handle;
	CURLcode res;

	//int
	FILE* save_file = fopen(filename,"w");
	if(save_file == NULL){
		printf("open save file fail!\n");
		return -1;
	}

	curl_handle = curl_easy_init();
	if(curl_handle){
		curl_easy_setopt(curl_handle, CURLOPT_URL, url);//set down load url
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, save_file);//set download file
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, recive_data_fun);//set call back fun
		curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, read_head_fun);//set call back fun
#ifdef CURL_DEBUG
		curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
#endif

		//start down load
		res = curl_easy_perform(curl_handle);
		printf("curl fetch code %d\n",res);
	}

	//release
	if(save_file){
		fclose(save_file);
		save_file = NULL;
	}
	if(curl_handle){
		curl_easy_cleanup(curl_handle);
	}
	if(url){
		free(url);
	}

	return 0;
}
