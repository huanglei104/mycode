#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//__attribute__ 的参数可以在前后加两个下划线, 防止有同名的宏定义

// __attribute((aligned())) 可以用在变量和结构体上，指定对齐地址
int abc __attribute((__aligned__(8))) = 10;

struct __attribute__((aligned(1))) person {
	char cc;
	int a;
	int b;
	short c;
};

struct __attribute__ ((aligned(8))) my_struct2 {
	int f[3];
};

// __attribute((packed)) 用在结构体上,使用紧凑模式
struct __attribute__ ((packed))abc {
	char a;
	short b;
	int c;
};


// __attribute((constructor)) 用在函数上，使函数在main之前运行。
// __attribute((destructor)) 用在函数上，使函数在exit或main返回之前运行。

void __attribute__((constructor)) test1(void)
{
        printf("test1.\n");
}

void __attribute__((constructor)) test2(void)
{
        printf("test2.\n");
}

void __attribute__((destructor)) test3(void)
{
        printf("hello1.\n");
}

void __attribute__((destructor)) test4(void)
{
        printf("hello2.\n");
}


int main(int argc, char *argv[])
{
	_Exit(1);
	struct person p1;
	struct my_struct2 m1;
	printf("%ld\n", sizeof(p1));
	printf("%ld\n", sizeof(m1));
	printf("%ld\n", sizeof(struct abc));
	printf("%p\n", &m1.f[0]);
	printf("%p\n", &m1.f[1]);
	printf("%p\n", &m1.f[2]);
	return 0;
}
