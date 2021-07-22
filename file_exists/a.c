#include <stdio.h>

int main(int argc, char *argv[])
{
    int a = 10;
    int *restrict p1;
    int *restrict p2;

    p1 = &a;
    p2 = &a;

    printf("%d\n", *p1);
    printf("%d\n", *p2);
    return 0;
}
