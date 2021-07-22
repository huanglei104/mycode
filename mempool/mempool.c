#include <stdio.h>
#include <stdlib.h>

typedef struct blk_t blk_t;

struct blk_t {
	void *start;
	ssize_t size;
	blk_t *next;
};


typedef struct {
	ssize_t total;
	void *start;
	blk_t *used;
	blk_t *free;
} mp_t;

static void blk_chain_add(blk_t *chain, blk_t *blk)
{
	blk_t *cur = chain;

	while (cur->next) cur = cur->next;

	cur->next = blk;
}

mp_t* mpcreate(ssize_t size)
{
	int blkn;
	void *mem;
	mp_t *mp;

	mp = malloc(sizeof(mp_t));
	if (!mp) return NULL;

	mem = malloc(size);
	if (!mem) return NULL;

	blkn = (size / 32) + (size % 32 != 0);

	mp->start = mem;
	mp->total = size;
	mp->used = NULL;
	mp->free = malloc(blkn * sizeof(blk_t));

	if (!mp->free) return NULL;

	for (int i = 0; i < blkn; i++) {
		mp->free[i].size = 32;
		mp->free[i].start = mp->start + i * 32;

		if (i < blkn - 1) mp->free[i].next = &mp->free[i + 1];
	}

	return mp;
}

void* mpalloc(mp_t *mp, const ssize_t size)
{
	blk_t *cur = mp->free;
	blk_t *end = cur;
	ssize_t total;
	int *blkn;

	if (!cur) return NULL;


	total = cur->size;
	blkn = cur->start;
	*blkn = 1;

	while (total < size + 4) {
		if (!end->next) return NULL;

		end = end->next;
		total += end->size;
		(*blkn)++;
	}


	if (mp->used)
		blk_chain_add(mp->used, cur);
	else
		mp->used = cur;

	mp->free = end->next;
	end->next = NULL;
	cur->size = total;

	return cur->start + 4;
}

void mpfree(mp_t *mp, void *p)
{
	if (!p) return;

	blk_t *blk = p - 4;
	blk->next = NULL;


	if (!mp->free) {
		mp->free = blk;

	} else {
		blk_chain_add(mp->free, blk);
	}

	if (mp->used == blk) {
		mp->used = blk->next;
	} else {
		mp->used->next
	}
}

int main(int argc, char *argv[])
{
	mp_t *mp;

	mp = mpcreate(1024);
	if (mp == NULL) {
		printf("mpcreate failed\n");
		return -1;
	}

	long *l;

	for (int i = 0; i < 2000; i++) {
		l = mpalloc(mp, sizeof(l));
		if (l == NULL) {
			printf("mpalloc failed %d\n", i);
			break;
		}

		*l = i;
		printf("%ld\n", *l);
	}


	return 0;
}
