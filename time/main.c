#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	time_t t = time(NULL);
	char *str = ctime(&t);

	printf("%s", str);

	struct tm *tmp = gmtime(&t);

	printf("%d-%d-%d:%d-%d-%d\n", tmp->tm_year + 1900, tmp->tm_mon + 1,
			tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

	tmp = localtime(&t);

	printf("%d-%d-%d:%d-%d-%d\n", tmp->tm_year + 1900, tmp->tm_mon + 1,
			tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

	printf("%s\n", asctime(tmp));
	return 0;
}
