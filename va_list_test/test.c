#include <stdarg.h>
#include <stdio.h>
#include <string.h>


//可变参数函数的第一个参数不一定要和可变量参数列表的参数类型一样

void foo(char *str, ...)
{
	int idx = 0;
	int ival;
	char *cval;
	char* ret = 0;
	va_list valist;
	char *c;

	va_start(valist, str);

	c = str;

	while (c) {
		c = strchr(c, '%');
		switch (*(c + 1)) {
			case 'd': {
						  ival = va_arg(valist, int);
						  printf("%d\n", ival);
					  }
					  break;
			case 's': {
						  cval = va_arg(valist, char*);
						  printf("%s\n", cval);
					  }
					  break;
		}
	}

	va_end(valist);
}
int main(int argc, char *argv[]) {
	foo("%d %s\n", 11, "hello");
	return 0;
}
