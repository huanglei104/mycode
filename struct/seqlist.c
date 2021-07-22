/*
 * 顺序表
 */

#include <stdio.h>

#define MAX 20

// 索引0位置不存储数据
typedef struct {
	int data[MAX];
	int len;
} seqlist_t;

typedef struct {
	int max;
	int start;
} blk_t;

void seqlist_init(seqlist_t *s)
{
	s->len = 0;
}

void seqlist_add(int key, seqlist_t *s)
{
	if (s->len >= MAX) return;

	s->data[++s->len] = key;
}

// 顺序查找
int seqsearch(int key, seqlist_t *s)
{
	int i = s->len;

	s->data[0] = key;

	while (s->data[i] != key) i--;

	return i;
}

// 二分查找, 要求数据是有序的
int binsearch(int key, seqlist_t *s)
{
	int low, mid, high;

	low = 1;
	high = s->len;

	while (low <= high) {
		mid = (low + high) / 2;

		if (s->data[mid] == key)
			return mid;

		else if (s->data[mid] < key)
			low = mid + 1;

		else
			high = mid - 1;
	}

	return 0;
}

// 分块查找，每个块大小固定为4
int blksearch(int key, seqlist_t *s, blk_t blks[], int blkn)
{
	int i, j;

	for (i = 0; i < blkn - 1; i++) {
		if (key <= blks[i].max) break;
	}

	for (j = 0; j < 4; j++) {
		if (s->data[j + blks[i].start] == key)
			return j + blks[i].start;
	}

	return 0;
}

//升序
void insertsort(seqlist_t *s)
{
	int i, j, key;

	for (i = 2; i <= s->len; i++) {
		j = i - 1;
		// 将待插入元素保存到key中，其位置会被覆盖
		key = s->data[i];
		//将所有大的元素向后移动一个位置,前面空出来的位置就是待插入的位置
		while (key < s->data[j] && j >= 1) {
			s->data[j + 1] = s->data[j];
			j--;
		}
		s->data[j + 1] = key;
	}
}

int main(int argc, char *argv[])
{
	int idx;
	seqlist_t list;

	seqlist_init(&list);

	seqlist_add(20, &list);
	seqlist_add(9, &list);
	seqlist_add(11, &list);
	seqlist_add(22, &list);
	seqlist_add(44, &list);
	seqlist_add(39, &list);
	seqlist_add(35, &list);
	seqlist_add(46, &list);

	blk_t blks[2];

	blks[0].start = 1;
	blks[0].max = 30;

	blks[1].start = 5;
	blks[1].max = 50;

	//idx = seqsearch(1, &list);
	//idx = binsearch(22, &list);
	//idx = blksearch(33, &list, blks, 2);
	//printf("idx %d\n", idx);

	insertsort(&list);
	for (int i = 1; i <= list.len; i++) {
		printf("%d ", list.data[i]);
	}

	return 0;
}
