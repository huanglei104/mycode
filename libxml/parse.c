#include <glib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>
#include <regex.h>
#include <stdbool.h>
#include "parse.h"
#include <fcntl.h>


Application default_app = {.sport = "1-65535", .dport = 80, .pport = 80, .l3_protocol = E_IPV4, .l4_protocol = E_TCP, .action = E_ALLOW, .timeout = 15};
Ruler default_ruler = {.action = E_ALLOW, .direction = E_DOWNSTREAM, .down_pattern = NULL, .up_pattern = NULL};
Cmd default_cmd = {.para = "", .offset = 0, .delimiter = " ", .end = "\r\n"};
Cmpn default_cmpn = {.operation = E_EQ, .offset = 0, .nnn = 8, .end = "\r\n"};

Application *app;
Ruler *ruler;
Cmd *cmd;
Cmpn *cmpn;

GHashTable	*g_apps;
short		g_action;
int 		g_enable;

typedef bool (*handler)(xmlNodePtr node);

typedef struct {
	char *name;
	handler handler;
} Element;

typedef struct {
	int min;
	int max;
} Range;

void gen_pattern_down(Ruler *ruler){

	guint i;
	char *p;
	ruler->down_pattern = calloc(1, 1600);
	p = ruler->down_pattern;
	for(i = 0; i < ruler->cmds->len; i++) {
		p += strlen(p);
		cmd = g_ptr_array_index(ruler->cmds, i);
		if(i == 0) {
			if(strlen(cmd->para) == 0) {
				sprintf(p, "%s%s", cmd->cmd, cmd->end);
			} else {
				sprintf(p, "%s%s\\S*%s\\S*%s", cmd->cmd, cmd->delimiter, cmd->para, cmd->end);
			}
		} else {
			if(strlen(cmd->para) == 0) {
				sprintf(p, ".{%d}%s%s", cmd->offset, cmd->cmd, cmd->end);
			} else {
				sprintf(p, ".{%d}%s%s\\S*%s\\S*%s", cmd->offset, cmd->cmd, cmd->delimiter, cmd->para, cmd->end);
			}
		}
	}
}

void gen_pattern_up(Ruler *ruler){
	guint i;
	char *p;
	Resp *resp;

	ruler->up_pattern = calloc(1, 1600);
	p = ruler->up_pattern;
	for(i = 0; i < ruler->cmds->len; i++) {
		p += strlen(p);
		cmd = g_ptr_array_index(ruler->cmds, i);
		resp = cmd->resp;
		sprintf(p, ".{%d}%s", resp->offset, resp->code);
	}
}

void gen_pattern(void *p, void *p2) {

	Ruler *ruler = p;

	if(ruler->direction == E_DOWNSTREAM) {
		gen_pattern_down(ruler);
	} else if(ruler->direction == E_UPSTREAM) {
		gen_pattern_up(ruler);
	} else {
		gen_pattern_down(ruler);
		gen_pattern_up(ruler);
	}
}

bool attribute_handler(xmlNodePtr node, char *string, char *_struct, GHashTable *tables[], Range ranges[]) {

	int offset;
	int index1 = 0;
	int index2 = 0;
	int intvalue;
	xmlAttr *attr;
	regex_t reg;
	regmatch_t match;
	xmlChar *value;
	char type;

	attr = node->properties;
	while(attr) {
		value = xmlGetProp(node, attr->name);
		regcomp(&reg, (char*)attr->name, REG_EXTENDED);
		if(regexec(&reg, string, 1, &match, 0) == 0) {
			type = *(string + match.rm_so - 1);
			offset = atoi(string + match.rm_eo);
			if(type == 'N') {
				intvalue = atoi((char*)value);
				if(intvalue < ranges[index2].min || intvalue > ranges[index2].max) {
					printf("value error\n");
					return false;
				}
				*(int*)(_struct + offset) = intvalue;
				index2++;
			} else if(type == 'S') {
				strcpy((_struct + offset), g_strcompress((char*)value));
			} else if(type == 'E') {
				gpointer p = g_hash_table_lookup(tables[index1], (char*)value);
				if(p) {
					*(int*)(_struct + offset) = (int)(long)p;
				} else {
					printf("unknow value %s\n", value);
					return false;
				}
				index1++;
			}
		};
		attr = attr->next;
	}
	return true;
}

int ruler_equal(const void *p1, const void *p2) {

	const Ruler *r1 = p1;
	const Ruler *r2 = p2;

	if(r1->action == r2->action && r1->direction == r2->direction) {
		return true;
	}
	return false;
}

bool enable_handler(xmlNodePtr node)  {

	xmlNodePtr cur = node->children;

	if(cur != NULL && cur->type == XML_TEXT_NODE && cur->next == NULL && cur->prev == NULL) {
		if(strcmp((char*)cur->content, "true") == 0) {
			g_enable = true;
			return true;
		}
		if(strcmp((char*)cur->content, "false") == 0) {
			g_enable = false;
			return true;
		}
		printf("unknow enable value\n");
		return false;
	}
	return true;
}

bool action_handler(xmlNodePtr node)  {
	xmlNodePtr cur;
	cur = node->children;
	if(cur != NULL && cur->type == XML_TEXT_NODE && cur->next == NULL && cur->prev == NULL) {
		if(strcmp((char*)cur->content, "allow") == 0) {
			g_action = DC_ALLOW;
			return true;
		}
		if(strcmp((char*)cur->content, "deny") == 0) {
			g_action = DC_DENY;
			return true;
		}
		printf("unknow action\n");
		return false;
	}
	return true;
}

bool app_handler(xmlNodePtr node) {

#define A Application

	bool ret;
	char string[128];
	char *key;
	GHashTable *tables[3];
	Range ranges[3];

	app = calloc(1, sizeof(A));
	key = calloc(1, 16);
	*app = default_app;

	ranges[0].min = 1;
	ranges[0].max = 65535;
	ranges[1].min = 1;
	ranges[1].max = 65535;
	ranges[2].min = 1;
	ranges[2].max = 120;


	tables[0] = g_hash_table_new(g_str_hash, g_str_equal);
	g_hash_table_insert(tables[0], "ipv4", (gpointer)E_IPV4);
	g_hash_table_insert(tables[0], "ipv6", (gpointer)E_IPV6);
	tables[1] = g_hash_table_new(g_str_hash, g_str_equal);
	g_hash_table_insert(tables[1], "tcp", (gpointer)E_TCP);
	g_hash_table_insert(tables[1], "udp", (gpointer)E_UDP);
	tables[2] = g_hash_table_new(g_str_hash, g_str_equal);
	g_hash_table_insert(tables[2], "allow", (gpointer)E_ALLOW);
	g_hash_table_insert(tables[2], "deny", (gpointer)E_DENY);

	memset(string, 0, 128);
	sprintf(string, "Ssport%ld,Ndport%ld,Npport%ld,El3_protocol%ld,El4_protocol%ld,Eaction%ld,Ntimeout%ld",
			offsetof(A, sport), offsetof(A, dport), offsetof(A, pport),
			offsetof(A, l3_protocol), offsetof(A, l4_protocol), offsetof(A, action), offsetof(A, timeout));
	ret = attribute_handler(node, string, (char*)app, tables, ranges);
	if(!ret) {
		printf("attribute_handler error\n");
		return ret;
	}
	app->rulers = g_ptr_array_new();
	sprintf(key, "%d%d%d", app->l3_protocol, app->l4_protocol, app->pport);
	g_hash_table_insert(g_apps, key, app);
	return true;
#undef A
}

bool ruler_handler(xmlNodePtr node) {

#define R Ruler

	guint index;
	bool ret;
	char string[128];
	GHashTable *tables[2];

	ruler = calloc(1, sizeof(R));
	*ruler = default_ruler;
	ruler->cmds = g_ptr_array_new();
	ruler->cmpns = g_ptr_array_new();

	tables[0] = g_hash_table_new(g_str_hash, g_str_equal);
	g_hash_table_insert(tables[0], "allow", (gpointer)E_ALLOW);
	g_hash_table_insert(tables[0], "deny", (gpointer)E_DENY);
	tables[1] = g_hash_table_new(g_str_hash, g_str_equal);
	g_hash_table_insert(tables[0], "allow", (gpointer)E_ALLOW);
	g_hash_table_insert(tables[1], "downstream", (gpointer)E_DOWNSTREAM);
	g_hash_table_insert(tables[1], "upstream", (gpointer)E_UPSTREAM);
	g_hash_table_insert(tables[1], "twoway", (gpointer)E_TWOWAY);

	memset(string, 0, 128);
	sprintf(string, "Eaction%ld,Edirection%ld", offsetof(R, action), offsetof(R, direction));
	ret = attribute_handler(node, string, (char*)ruler, tables, NULL);
	if(!ret) {
		return false;
	}
	ret = g_ptr_array_find_with_equal_func(app->rulers, ruler, ruler_equal, &index);
	if(ret) {
		ruler = g_ptr_array_index(app->rulers, index);
	} else {
		g_ptr_array_add(app->rulers, ruler);
	}
	return true;
#undef R
}

bool cmd_handler(xmlNodePtr node) {

#define C Cmd
	char string[128];
	Range ranges[1];

	ranges[0].min = 0;
	ranges[0].max = 4194303;
	cmd = calloc(1, sizeof(C));
	*cmd = default_cmd;

	memset(string, 0, 128);
	sprintf(string, "Scmd%ld,Spara%ld,Noffset%ld,Sdelimiter%ld,Send%ld", offsetof(C, cmd), offsetof(C, para), offsetof(C, offset),
			offsetof(C, delimiter), offsetof(C, end));
	attribute_handler(node, string, (char*)cmd, NULL, ranges);
	g_ptr_array_add(ruler->cmds, cmd);
	return true;
#undef C
}

bool resp_handler(xmlNodePtr node) {

#define R Resp
	char string[128];
	R *resp;
	Range ranges[1];

	ranges[0].min = 0;
	ranges[0].max = 4194303;
	resp = calloc(1, sizeof(R));

	memset(string, 0, 128);
	sprintf(string, "Scode%ld,Noffset%ld", offsetof(R, code), offsetof(R, offset));
	attribute_handler(node, string, (char*)resp, NULL, ranges);
	cmd->resp = resp;
	return true;
#undef R
}
bool cmpn_handler(xmlNodePtr node) {

#define C Cmpn
	bool ret;
	char string[128];
	GHashTable *table[1];
	Range ranges[3];

	ranges[0].min = 0;
	ranges[0].max = INT32_MAX;
	ranges[1].min = 0;
	ranges[1].max = 4194303;
	ranges[2].min = 1;
	ranges[2].max = 8;

	table[0] = g_hash_table_new(g_str_hash, g_str_equal);
	g_hash_table_insert(table[0], ">", (gpointer)E_GT);
	g_hash_table_insert(table[0], "=", (gpointer)E_EQ);
	g_hash_table_insert(table[0], "<", (gpointer)E_LG);
	cmpn = calloc(1, sizeof(C));
	//*cmpn = default_cmpn;

	memset(string, 0, 128);
	sprintf(string, "Nvalue%ld,Eoperation%ld,Noffset%ld,Nnnn%ld,Send%ld", offsetof(C, value), offsetof(C, operation), offsetof(C, offset), offsetof(C, nnn), offsetof(C, end));
	ret = attribute_handler(node, string, (char*)cmpn, table, ranges);
	if(!ret) {
		return false;
	}
	g_ptr_array_add(ruler->cmpns, cmpn);
	return true;
#undef C
}

bool cmpm_handler(xmlNodePtr node) {

#define C Cmpm
	char string[128];
	C *cmpm;
	GHashTable *table[1];
	Range ranges[3];

	ranges[0].min = 0;
	ranges[0].max = INT32_MAX;
	ranges[1].min = 0;
	ranges[1].max = 4194303;
	ranges[2].min = 1;
	ranges[2].max = 8;

	cmpm = calloc(1, sizeof(C));
	table[0] = g_hash_table_new(g_str_hash, g_str_equal);
	g_hash_table_insert(table[0], ">", (gpointer)E_GT);
	g_hash_table_insert(table[0], "=", (gpointer)E_EQ);
	g_hash_table_insert(table[0], "<", (gpointer)E_LG);

	memset(string, 0, 128);
	sprintf(string, "Nvalue%ld,Eoperation%ld,Noffset%ld,Nnnn%ld,Send%ld", offsetof(C, value), offsetof(C, operation), offsetof(C, offset), offsetof(C, nnn), offsetof(C, end));
	attribute_handler(node, string, (char*)cmpm, table, ranges);
	cmpn->cmpm = cmpm;
	return true;
#undef C
}

GHashTable *table;
Element elements[] = {
	{.name = "xml", .handler = NULL},
	{.name = "enable", .handler = enable_handler},
	{.name = "action", .handler = action_handler},
	{.name = "application", .handler = app_handler},
	{.name = "ruler", .handler = ruler_handler},
	{.name = "cmd", .handler = cmd_handler},
	{.name = "resp", .handler = resp_handler},
	{.name = "cmpn", .handler = cmpn_handler},
	{.name = "cmpm", .handler = cmpm_handler},
	{.name = NULL},
};

bool parse_node(xmlNodePtr node) {

	bool ret;
	xmlNodePtr child;

	if(node->type == XML_ELEMENT_NODE) {
		Element *e = g_hash_table_lookup(table, node->name);
		if(e) {
			if(e->handler) {
				ret = e->handler(node);
				if(!ret) {
					return false;
				}
			}
		} else {
			printf("unknow element %s\n", node->name);
			return false;
		}
		child = node->children;
		while(child) {
			ret = parse_node(child);
			if(!ret) {
				printf("parse_node error %s\n", child->name);
				return false;
			}
			child = child->next;
		}
	}
	return true;
}

bool parse_doc(char *file) {

	xmlDocPtr doc;
	xmlNodePtr root;
	Element *e;
	bool ret;

	doc = xmlParseFile(file);

	if(doc == NULL) {
		return false;
	}

	e = elements;
	table = g_hash_table_new(g_str_hash, g_str_equal);
	while(e->name) {
		g_hash_table_insert(table, e->name, e);
		e++;
	}
	g_apps = g_hash_table_new(g_str_hash, g_str_equal);

	root = xmlDocGetRootElement(doc);

	if(root == NULL) {
		printf("empty document\n");
		xmlFreeDoc(doc);
		return false;
	}
	ret = parse_node(root);
	if(ret) {
		GList *apps = g_hash_table_get_values(g_apps);
		while(apps) {
			Application *app = apps->data;
			g_ptr_array_foreach(app->rulers, gen_pattern, NULL);
			apps = apps->next;
		}
	}

	xmlFreeDoc(doc);
	return ret;
}

void show_cmd(gpointer p, gpointer user_data) {
	Cmd *cmd = p;
	printf("        cmd: %s %s %s %s %d\n", cmd->cmd, cmd->delimiter, cmd->para, cmd->end, cmd->offset);
	if(cmd->resp) {
		printf("        resp: %s %d\n", cmd->resp->code, cmd->resp->offset);
	}
}

void show_cmpn(gpointer p, gpointer user_data) {
	Cmpn *cmpn = p;
	printf("        Cmpn: %d %d nnn %d %d %s\n", cmpn->value, cmpn->offset, cmpn->nnn, cmpn->operation, cmpn->end);
	if(cmpn->cmpm) {
		printf("        Cmpm: %d %d %d %d %s\n", cmpn->cmpm->value, cmpn->cmpm->offset, cmpn->cmpm->nnn, cmpn->cmpm->operation, cmpn->cmpm->end);
	}
}

void show_ruler(gpointer p, gpointer user_data) {
	Ruler *r = p;
	printf("    ruler: %d %d d:%s| u:%s|\n", r->action, r->direction, r->down_pattern, r->up_pattern);
	g_ptr_array_foreach(r->cmds, show_cmd, NULL);
	g_ptr_array_foreach(r->cmpns, show_cmpn, NULL);
}

void show_app(gpointer key, gpointer value, gpointer user_data) {
	Application *app = value;
	printf("app: %s %d %d %d %d %d %d\n", app->sport, app->dport, app->pport, app->l3_protocol, app->l4_protocol, app->action, app->timeout);
	g_ptr_array_foreach(app->rulers, show_ruler, NULL);
}

int main(int argc, char **argv)
{

	xmlSchemaPtr xsp;
	xmlSchemaParserCtxtPtr xspcp;

	xspcp = xmlSchemaNewParserCtxt("/etc/jsac/custom_app.xsd");
	if (xspcp == NULL) {
		printf("error\n");
		return 0;
	}

	xsp = xmlSchemaParse(xspcp);
	if (xsp == NULL) {
		printf("error\n");
		return 0;
	}


	if(parse_doc("/etc/jsac/custom_app.xml")) {
		g_hash_table_foreach(g_apps, show_app, NULL);
	}
	return 0;
}
