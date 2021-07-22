#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_email_address_from_sender(char *sender)
{
    char *email;
    regex_t reg;
    regmatch_t match;

    regcomp(&reg, "[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+", REG_EXTENDED | REG_ICASE);
    if (regexec(&reg, sender, 1, &match, 0) != REG_NOMATCH) {
        email = calloc(1, sizeof( match.rm_eo - match.rm_so) + 1);
        memcpy(email, sender + match.rm_so, match.rm_eo - match.rm_so);
        return email;
    }

    return NULL;
}


int main(int argc, char *argv[])
{

	char *email = get_email_address_from_sender("马志浩 <mazhihao@jusontech.com>");
	printf("%s\n", email);

	return 0;
}
