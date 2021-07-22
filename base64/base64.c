#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
  
/*char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  

char *base64_encode(char *str) {  
	long len;  
	long str_len;  
	char *res;  
	int i,j;  

	str_len=strlen(str);  
	if(str_len % 3 == 0)  
		len=str_len/3*4;  
	else  
		len=(str_len/3+1)*4;  

	res=malloc(sizeof(unsigned char)*len+1);  
	res[len]='\0';  

	//以3个8位字符为一组进行编码  
	for(i=0,j=0;i<len-2;j+=3,i+=4) {  
		res[i]=base64_table[str[j]>>2]; //取出第一个字符的前6位并找出对应的结果字符  
		res[i+1]=base64_table[(str[j]&0x3)<<4 | (str[j+1]>>4)]; //将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符  
		res[i+2]=base64_table[(str[j+1]&0xf)<<2 | (str[j+2]>>6)]; //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符  
		res[i+3]=base64_table[str[j+2]&0x3f]; //取出第三个字符的后6位并找出结果字符  
	}  

	switch(str_len % 3) {  
		case 1:  
			res[i-2]='=';  
			res[i-1]='=';  
			break;  
		case 2:  
			res[i-1]='=';  
			break;  
	}  

	return res;  
} */ 

int gb2utf(char *buf, size_t inlen) {

	size_t sz = 1024 * 1024;
	size_t outlen = sz;
	char *in = buf;
	char *out;
	char *tmp_str;

	tmp_str = malloc(sz);
	out = tmp_str;

	memset(tmp_str, 0, sz);

	iconv_t cd = iconv_open("UTF-8", "GB18030");
	if (cd == (iconv_t)-1) {
		perror("iconv_open");
		return -1;
	}
	if (iconv(cd, &in, &inlen, &out, &outlen) == (size_t)-1) {
		perror("iconv");
		iconv_close(cd);
		return -1;
	}
	iconv_close(cd);
	return 0;
}

void base64_decode(char *code, char *dest) {
	int table[]={0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,62,0,0,0,
		63,52,53,54,55,56,57,58,
		59,60,61,0,0,0,0,0,0,0,0,
		1,2,3,4,5,6,7,8,9,10,11,12,
		13,14,15,16,17,18,19,20,21,
		22,23,24,25,0,0,0,0,0,0,26,
		27,28,29,30,31,32,33,34,35,
		36,37,38,39,40,41,42,43,44,
		45,46,47,48,49,50,51
	};  
	long len;  
	long str_len;  
	char *res;  
	int i,j;  

	len=strlen(code);  
	if(strstr(code,"=="))  
		str_len=len/4*3-2;  
	else if(strstr(code,"="))  
		str_len=len/4*3-1;  
	else  
		str_len=len/4*3;  

	res=malloc(sizeof(char)*str_len+1);  
	res[str_len]='\0';  

	for(i=0,j=0;i < len-2;j+=3,i+=4) {  
		res[j]=(( char)table[(int)code[i]])<<2 | ((( char)table[(int)code[i+1]])>>4);
		res[j+1]=((( char)table[(int)code[i+1]])<<4) | ((( char)table[(int)code[i+2]])>>2);
		res[j+2]=((( char)table[(int)code[i+2]])<<6) | (( char)table[(int)code[i+3]]);
	}
	memcpy(dest, res, strlen(res) + 1);
	free(res);

} 

int num_strchr(const char *str, char c) // 
{
    const char *pindex = strchr(str, c);
    if (NULL == pindex){
        return -1;
    }
    return pindex - str;
}

const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char padding_char = '=';

int base64_decode2(const char * base64, char * dedata)
{
    int i = 0, j=0;
    int trans[4] = {0,0,0,0};
    for (;base64[i]!='\0';i+=4){
        // 每四个一组，译码成三个字符
        trans[0] = num_strchr(base64char, base64[i]);
        trans[1] = num_strchr(base64char, base64[i+1]);
        // 1/3
        dedata[j++] = ((trans[0] << 2) & 0xfc) | ((trans[1]>>4) & 0x03);
 
        if (base64[i+2] == '='){
            continue;
        }
        else{
            trans[2] = num_strchr(base64char, base64[i + 2]);
        }
        // 2/3
        dedata[j++] = ((trans[1] << 4) & 0xf0) | ((trans[2] >> 2) & 0x0f);
 
        if (base64[i + 3] == '='){
            continue;
        }
        else{
            trans[3] = num_strchr(base64char, base64[i + 3]);
        }
 
        // 3/3
        dedata[j++] = ((trans[2] << 6) & 0xc0) | (trans[3] & 0x3f);
    }
 
    dedata[j] = '\0';
 
    return 0;
}

int main(int argc,char *argv[])  {  

	//char str[] = "RlRQ0K3S6bXE1ve2r8Sjyr3T67G7tq/Eo8q9LmRvY3g=";
	char str[] = "\r\n.\r\n";
	base64_decode(str, str);
	printf("%d\n", str[0]);   
	//gb2utf(str, strlen(str));
	//printf("%s\n", str);   

	return 0;  
}
