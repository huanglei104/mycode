#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>

#define OPENSSLKEY "test.key"
#define PUBLICKEY "test_pub.key"

char *encrypt(char *str,char *path_key)
{
	char *p_en=NULL;
	RSA *p_rsa=NULL;
	FILE *fp=NULL;
	int rsa_len=0;

	if((fp=fopen(path_key,"rb"))==NULL)
	{
		printf("open %s failure ",path_key);
		goto clean;
	}

	if((p_rsa=PEM_read_RSA_PUBKEY(fp,NULL,NULL,NULL))==NULL)
	{
		ERR_print_errors_fp(stdout);
		goto clean;
	}
	rsa_len=RSA_size(p_rsa);

	p_en=(char *)malloc(rsa_len+1);
	if(!p_en)
	{
		printf("malloc failure");
		goto clean;
	}
	memset(p_en,0,rsa_len+1);

	if(RSA_public_encrypt(rsa_len,(unsigned char *)str,(unsigned char *)p_en,p_rsa,RSA_NO_PADDING)<0)
	{
		printf("RSA_public_encrypt error ");
		goto clean;
	}

clean:
	if(p_rsa)    RSA_free(p_rsa);
	if(fp)       fclose(fp);

	return p_en;
}

char *decrypt(char *str,char *path_key)
{
	char *p_de=NULL;
	RSA *p_rsa=NULL;
	FILE *fp=NULL;
	int rsa_len=0;//initialize to zero

	if((fp=fopen(path_key,"rb"))==NULL)
	{
		printf("open %s error ",path_key);
		goto clean;
	}

	if((p_rsa=PEM_read_RSAPrivateKey(fp,NULL,NULL,NULL))==NULL)
	{
		ERR_print_errors_fp(stdout);
		goto clean;
	}

	rsa_len=RSA_size(p_rsa);

	p_de=(char *)malloc(rsa_len+1);

	if(!p_de)
	{
		printf("malloc error ");
		goto clean;
	}
	memset(p_de,0,rsa_len+1);

	if(RSA_private_decrypt(rsa_len,(unsigned char *)str,(unsigned char *)p_de,p_rsa,RSA_NO_PADDING)<0)
	{
		printf("RSA_private_decrypt error ");
		goto clean;
	}
clean:
	if(p_rsa)    RSA_free(p_rsa);
	if(fp)       fclose(fp);

	return p_de;
}



int main(int argc,char **argv)
{
	char *source = "i like dancing !!!";
	char *ptf_en;
	char *ptf_de;

	printf("source is : %s\n",source);

	ptf_en = encrypt(source,PUBLICKEY);

	printf("pth_ed is : %s\n",ptf_en);

	ptf_de=decrypt(ptf_en,OPENSSLKEY);

	printf("ptf_de is : %s\n",ptf_de);

	free(ptf_en);
	free(ptf_de);
	return 0;
}
