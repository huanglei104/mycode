#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	char line[1024];
	FILE *file;
	file = fopen("/tmp/http.txt", "r");
	while(fgets(line, 1024, file)) {
		printf("%d\n", atoi(line));
	}
	return 0;
}
