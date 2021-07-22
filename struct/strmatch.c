#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int bruteforce(char *str, char *pattern)
{
	char *p1 = str;
	char *p2 = pattern;
	int len1 = strlen(str);
	int len2 = strlen(pattern);


	for (int i = 0; i <= len1 - len2; i++) {
		int j;

		for (j = 0; j < len2; j++) {
			if (pattern[j] != str[i + j])
				break;
		}

		if (j == len2) return i;
	}

	return -1;
}

int bruteforce2(char *str, char *pattern)
{
	char *p1 = str;
	char *p2 = pattern;
	int len1 = strlen(str);
	int len2 = strlen(pattern);

	int i, j;

	for (i = 0, j = 0; (i < len1) && (j < len2); i++) {
		if (str[i] == pattern[j]) {
			j++;
		} else {
			i -= j;
			j = 0;
		}
	}

	if (j == len2) return i - len2;

	return -1;
}

//构造部分匹配表
void Next(char *str,int *next){
    int i = 1, j = 0;

    next[1]=0;

    while (i < strlen(str)) {
        if (j == 0 || str[i-1] == str[j-1]) {
            i++;
            j++;
            next[i] = j;
        } else{
            j = next[j];
        }
    }
}

// kmp算法的讲解：http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
int kmp(char *S,char *T){
    int next[10];
    Next(T,next);

    int i=1;
    int j=1;

    while (i<=strlen(S)&&j<=strlen(T)) {
        //j==0:代表模式串的第一个字符就和当前测试的字符不相等；S[i-1]==T[j-1],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
        if (j==0 || S[i-1]==T[j-1]) {
            i++;
            j++;
        }
        else{
            j=next[j];//如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
        }
    }
    if (j>strlen(T)) {//如果条件为真，说明匹配成功
        return i-(int)strlen(T);
    }
    return -1;
}

int main(int argc, char *argv[])
{
	int idx = kmp("hello world kaka, xixi, mam, haha, wawa, baba, mama", ", mama");
	printf("idx %d\n", idx);;
	return 0;
}

