#include <stdio.h>

typedef struct {
	int start;
	int max;
} block_t;


int block_search(int array[], block_t blks[], int blkn, int val)
{
	int i, j;

	int low, high, mid;

	//对索引表进行二分查找

	low = 0;
	high = blkn - 1;

	while (low < high) {
		mid = (low + high) / 2;
		if (blks[mid].max >= val)
			high = mid;
		else
			low = mid + 1;
	}

	i = blks[low].start;

	for (j = 0; j < 4; j++) {
		if (array[i + j] == val)
			return i + j;
	}

	return -1;

	//对索引表进行顺序查找

	for (i = 0; i < blkn; i++) {
		if (val <= blks[i].max) break;
	}

	i = blks[i].start;

	for (j = 0; j < 4; j++) {
		if (array[i + j] == val)
			return i + j;
	}

	return -1;
}

int bin_search(int array[], int len, int value)
{
	int mid;
	int low = 0;
	int hight = len - 1;

	while (low <= hight) {
		mid = (low + hight) / 2;

		if (array[mid] == value)
			return mid;

		else if (array[mid] < value)
			low = mid + 1;

		else
			hight = mid - 1;
	}

	return -1;
}

int main(int argc, char *argv[])
{
	int idx;

	int array[] = {3, 7, 9, 11, 55, 44, 55};
	idx = bin_search(array, 7, 3);
	printf("%d\n", idx);

	block_t blks[4];
	int array2[] = {9, 3, 8, 4, 13, 19, 15, 11, 20, 29, 22, 27, 46, 41, 55, 48};
	blks[0].start = 0;
	blks[0].max = 10;

	blks[1].start = 4;
	blks[1].max = 20;

	blks[2].start = 8;
	blks[2].max = 30;

	blks[3].start = 12;
	blks[3].max = 40;


	idx = block_search(array2, blks, 4, 22);
	printf("%d\n", idx);

	return 0;
}
