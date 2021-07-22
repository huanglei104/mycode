#include <glib.h>

#define DC_ALLOW	1
#define DC_DENY		2

typedef enum {
	E_ALLOW = 0x10,
	E_DENY = 0x20
} ACTION;

typedef enum {
	E_IPV4 = 0x10,
	E_IPV6 = 0x20
} L3P;

typedef enum {
	E_TCP = 0x10,
	E_UDP = 0x20
} L4P;

typedef enum {
	E_DOWNSTREAM = 0x10,
	E_UPSTREAM = 0x20,
	E_TWOWAY = 0x30
} DIRECTORY;

typedef enum {
	E_GT = 0x10,
	E_LG = 0x20,
	E_EQ = 0x30
} OPERTATE;

typedef struct _resp {
        char	code[32];
        int	offset;
} Resp;

typedef struct _cmpn{    
	int	value;
	int 	nnn;
	int	offset;
        char	end[16];
	OPERTATE operation;
        struct _cmpn *cmpm;
} Cmpn;    
                        
typedef Cmpn Cmpm;

typedef struct _cmd {    
        char	cmd[32];
        char	para[128];    
        char	end[16];
	int	offset;
        char	delimiter[16];    
        Resp	*resp;
} Cmd;                                            
        
typedef struct _ruler { 
        long	index;
	ACTION	action;
	DIRECTORY direction;
        char *down_pattern;
        char *up_pattern;
        GPtrArray *cmds;
        GPtrArray *cmpns; 
} Ruler;

typedef struct _app{
        long	index;        
        char	sport[12];   
        int	dport;
        int	pport;
        L3P	l3_protocol;
	L4P	l4_protocol;
	ACTION	action;
	int 	timeout;
        GPtrArray *rulers;
} Application;
