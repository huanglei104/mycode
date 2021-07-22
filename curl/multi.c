#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>
#include <stdlib.h>

//#define CURL_DEBUG 1
#define CURL_WAIT_TIMEOUT_MSECS 1000 //1s
#define CURL_MULIT_MAX_NUM 5

typedef struct curl_obj{
    CURL* curl_handle;
    FILE* save_file;
    char* fetch_url;
    size_t (*recive_data_fun)( void *ptr, size_t size, size_t nmemb, void *stream);
    size_t (*read_head_fun)( void *ptr, size_t size, size_t nmemb, void *stream);
}curl_obj;

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
        printf("ERROR----arg1 is url; arg2 is out file\n");
        return -1;
    }

    char* outfile_name[CURL_MULIT_MAX_NUM] = {0};
    curl_obj obj[CURL_MULIT_MAX_NUM];
    int mulit_h_num = ((argc -1) < CURL_MULIT_MAX_NUM)? (argc -1):CURL_MULIT_MAX_NUM;

    CURLM *multi_handle = curl_multi_init();
    for(int i=0;i<mulit_h_num;i++){
        obj[i].fetch_url = strdup( argv[i+1]);//need free
        char out_filename[1024] ;
        sprintf(out_filename,"/storage/external_storage/sda4/%s",strrchr( argv[i+1], '/'));
        printf("----save_file[%d] [%s]\n",i,out_filename);
        obj[i].save_file = fopen(out_filename,"w");
        if(!obj[i].save_file){
            printf("ERROR----fail!!!\n");
            goto release;
        }

        obj[i].curl_handle = curl_easy_init();
        obj[i].recive_data_fun = recive_data_fun;
        obj[i].read_head_fun = read_head_fun;
        if(obj[i].curl_handle){
            curl_easy_setopt(obj[i].curl_handle, CURLOPT_NOSIGNAL, 1L);
            curl_easy_setopt(obj[i].curl_handle, CURLOPT_URL, obj[i].fetch_url);//set down load url
            curl_easy_setopt(obj[i].curl_handle, CURLOPT_WRITEDATA, obj[i].save_file);//set download file
            curl_easy_setopt(obj[i].curl_handle, CURLOPT_WRITEFUNCTION, obj[i].recive_data_fun);//set call back fun
#ifdef CURL_DEBUG
            curl_easy_setopt(obj[i].curl_handle, CURLOPT_VERBOSE, 1);
#else
            curl_easy_setopt(obj[i].curl_handle, CURLOPT_HEADERFUNCTION, obj[i].read_head_fun);//set call back fun
#endif
            if(multi_handle) curl_multi_add_handle(multi_handle, obj[i].curl_handle);//add task
        }else{
            printf("fetch [%s]----ERROR!!!\n",obj[i].fetch_url );
            //goto release;
        }
    }

    int still_running,repeats;
    curl_multi_perform(multi_handle, &still_running);
    do {
        int numfds = 0;
        long timeout_ms = CURL_WAIT_TIMEOUT_MSECS;
        curl_multi_timeout(multi_handle, &timeout_ms);//get timeout ms instead
        CURLMcode retcode = curl_multi_wait(multi_handle, NULL, 0, timeout_ms, &numfds);
        if (retcode != CURLM_OK) {
            printf("ERROR----curl_multi_wait  errorcode[%d]\n",retcode);
            break;
        }
        /* 'numfds' being zero means either a timeout or no file descriptors to
           wait for. Try timeout on first occurrence, then assume no file
           descriptors and no file descriptors to wait for means wait for 10
           milliseconds. */
        if(!numfds) {
            if(repeats++ > 60){
                printf("ERROR----timeout break!!! \n");
                break;
            }else{
                usleep(10*1000);  /* sleep 10 milliseconds */
                continue;
            }
        }
        else{
            repeats = 0;
        }

        retcode = curl_multi_perform(multi_handle, &still_running);
        if (retcode != CURLM_OK) {
            printf("ERROR----curl_multi_perform  errorcode[%d]\n",retcode);
            break;
        }
        //printf("still_running[%d]\tnumfds[%d]\n",still_running,numfds );

        int msgs_left = 0;
        CURLMsg *msg = NULL;
        while ((msg = curl_multi_info_read(multi_handle, &msgs_left)) != NULL){
            if (msg->msg == CURLMSG_DONE) {
                long http_response_code = -1;
                char* http_url = NULL;
                curl_easy_getinfo(msg->easy_handle, CURLINFO_RESPONSE_CODE, &http_response_code);
                curl_easy_getinfo(msg->easy_handle, CURLINFO_EFFECTIVE_URL, &http_url);
                printf("[%s]fetch done, response[%ld]\n",http_url,http_response_code );
            }
        }
    } while (still_running);

release:
     printf("release\n");
     for(int i=0;i<mulit_h_num;i++){
        if(obj[i].curl_handle){
            curl_multi_remove_handle(multi_handle, obj[i].curl_handle);
            curl_easy_cleanup(obj[i].curl_handle);
        }
        if(obj[i].save_file){
            fclose(obj[i].save_file);
            obj[i].save_file = NULL;
        }
        if(obj[i].fetch_url){
            free(obj[i].fetch_url);
            obj[i].fetch_url = NULL;
        }
    }
    if(multi_handle !=NULL){
        curl_multi_cleanup(multi_handle);
    }

    return 0;
}
