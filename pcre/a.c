#include <pcre.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

	int ovector[20];
	int erroffset;
	char *src = "abc.abc";
	int rc, i;

	const char *error;
	pcre *re = pcre_compile(".*", 0, &error, &erroffset, NULL);
	if(re) {
		rc = pcre_exec(re, NULL, "abc.abc", 7, 0, 0, ovector, 20);
		if(rc < 0) {
			printf("exec error\n");
			return 0;
		}
		printf("matched\n");
		for(i = 0; i < rc; i++) {
			char *substring_start = src + ovector[2*i];
			int substring_length = ovector[2*i+1] - ovector[2*i];
			printf("%2d: %.*s\n", i, substring_length, substring_start);
		}
		return 0;
	}
	printf("compile error\n");
	return 0;
}
