#include <stdio.h>

typedef int (*initcall_t)(int a, char *s);
extern initcall_t __initcall_start, __initcall_end;

#define __init_call	__attribute__ ((unused,__section__ ("function_ptrs")))

#define module_init(fn) \
	static initcall_t __initcall_##fn __init_call = fn
/*上述宏定义名为"__initcall_函数名"的函数指针,且将函数指针放在function_ptrs节
  这个函数指针，指向fn(fn函数则放在code_segment节中)*/

static int my_init1(int a, char *s)
{
	printf("%d %s\n", a, s);
	return 0;
}

static int my_init2(int a, char *s)
{
	printf("%d %s\n", a, s);
	return 0;
}

static int my_init3(int a, char *s)
{
	printf("%d %s\n", a, s);
	return 0;
}

module_init(my_init1);
module_init(my_init2);
static initcall_t __initcall_my_init3 __attribute__((unused, __section__ ("function_ptrs"))) = my_init3;

void do_initcalls()
{
	int i = 10;
	initcall_t *call_p  = &__initcall_start;

	do {
		printf ("call_p: %p\n", call_p);
		(*call_p)(i++, "hello");
		call_p++;
	} while (call_p < &__initcall_end);
}

int main(int argc, char *argv[])
{
	do_initcalls ();

	return 0;
}
