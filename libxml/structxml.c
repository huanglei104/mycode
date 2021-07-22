
/** struct2xml.c */
 
#include <stdio.h>
#include <unistd.h>
#include "soapStub.h"
#include "soapH.h"
#include "nsmap.h"
 
/**
 * struct2xml: transfer struct to xml 
 * strname: the struct name
 * strvar: a struct instance name
 * xmlbuf: buffer store the result
 * buflen: buffer size
 */
#define struct2xml(strname, strvar, xmlbuf, buflen)	\
	do {						\
		struct soap soap = {0};			\
		struct strname *param = &strvar;	\
		int pfd[2];				\
		if (pipe(pfd))				\
			break;				\
		soap_init(&soap);			\
		soap.sendfd = pfd[1];			\
		soap_write_PointerTo##strname(&soap, (struct strname * const*) &param); \
		read(pfd[0], xmlbuf, buflen - 1);	\
		close(pfd[0]);				\
		close(pfd[1]);				\
		soap_destroy(&soap);			\
		soap_end(&soap);			\
		soap_done(&soap);			\
	} while (0)
 
int main(int argc, char *argv[])
{
	struct RequestUpdate req = {0};
	snprintf(req.Action, sizeof(req.Action), "%s", "Action");
	snprintf(req.Auth.Username, sizeof(req.Auth.Username), "%s", "Username");
	snprintf(req.Auth.Password, sizeof(req.Auth.Password), "%s", "Password");
	snprintf(req.Auth.Createtm, sizeof(req.Auth.Createtm), "%s", "Createtm");
	snprintf(req.Auth.Nonce, sizeof(req.Auth.Nonce), "%s", "Nonce");
	snprintf(req.DevInfo.Product, sizeof(req.DevInfo.Product), "%s", "Product");
	snprintf(req.DevInfo.Firmware, sizeof(req.DevInfo.Firmware), "%s", "Firmware");
	snprintf(req.DevInfo.SN, sizeof(req.DevInfo.SN), "%s", "SN");
 
	char xmldata[2048] = {0};
	int xmlsize = sizeof(xmldata);
 
	struct2xml(RequestUpdate, req, xmldata, sizeof(xmldata));
	printf("%s\n", xmldata);
 
	return 0;
}




/** xml2struct.c */
 
#include <stdio.h>
#include <string.h>
#include "soapStub.h"
#include "soapH.h"
#include "nsmap.h"
 
/**
 * xml2struct: transfer xml to struct
 * strname: the struct name
 * strvar: a struct instance name
 * xmlbuf: xml string 
 */
#define xml2struct(strname, strvar, xmlbuf)				\
	do {								\
		struct soap soap;					\
		int pfd[2];						\
		if (pipe(pfd))						\
			break;						\
		write(pfd[1], xmlbuf, strlen(xmlbuf));			\
		soap_init(&soap);					\
		soap_begin(&soap);					\
		soap.recvfd = pfd[0];					\
		soap_begin_recv(&soap);					\
		if (!soap_get_##strname(&soap, &strvar, NULL, NULL))	\
			memset(&strvar, 0, sizeof(struct strname));	\
		soap_end_recv(&soap);					\
		soap_destroy(&soap);					\
		soap_end(&soap);					\
		soap_done(&soap);					\
		close(pfd[0]);						\
		close(pfd[1]);						\
	} while (0)
 
int main()
{
	char *xmldata = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<RequestUpdate><Action>Action</Action><Auth><Username>Username</Username><Password>Password</Password><Createtm>Createtm</Createtm><Nonce>Nonce</Nonce></Auth><DevInfo><Product>Product</Product><Firmware>Firmware</Firmware><SN>SN</SN></DevInfo></RequestUpdate>";
 
	struct RequestUpdate req = {0};
	xml2struct(RequestUpdate, req, xmldata);
	
	printf("%s,%s,%s,%s,%s,%s,%s,%s\n", req.Action, req.Auth.Username, req.Auth.Password, req.Auth.Createtm, req.Auth.Nonce, req.DevInfo.Product, req.DevInfo.Firmware, req.DevInfo.SN);
	return 0;

}

