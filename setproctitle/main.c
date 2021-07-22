#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define ENV_SIZE (envp - environ) * sizeof(char*)
extern char **environ;


const char *new_name = "new_name aa aa aa";

int main(int argc, char *argv[])
{

	char **new_env = NULL, **envp = environ;
	char *argvp = argv[0];

	while(*envp) envp++;
	new_env = malloc(ENV_SIZE);
	memcpy(new_env, environ, ENV_SIZE);
	environ = new_env;

	while(*new_env) {
		printf("%s\n", *new_env);
		new_env++;
	}
	memcpy(argvp, new_name, strlen(new_name) + 1);
	pause();

	return 0;
}
