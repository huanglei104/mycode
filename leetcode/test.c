#include <stdio.h>
#include <glib.h>

void test_fibonacci()
{
	int fibonacci(int i)
	{
		if ( i == 0 || i == 1) {
			return i;
		} else {
			return fibonacci(i - 1) + fibonacci(i - 2);
		}
	}

	printf("%d\n", fibonacci(10));
}

void twosum(int array[], int len, int value)
{
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (array[i] + array[j] == value) {
				printf("%d, %d\n", i, j);
				return;
			}
		}
	}

	printf("no elements\n");
}

void twosum2(int array[], int len, int value)
{
	int hv;
	GHashTable *ht = g_hash_table_new(g_int_hash, g_int_equal);

	for (int i = 0; i < len; i++) {
		hv = value - array[i];
		g_hash_table_insert(ht, &array[i], &hv);
	}

	for (int i = 0; i < len - 1; i++) {
		if (g_hash_table_lookup(ht, &array[i])) {
			printf("%d, %d\n", i, j);
		}
	}

	printf("no elements\n");
}

int main(int argc, char *argv[])
{
	int array[] = {2, 7, 11, 15};
	//test_fibonacci();
	twosum(array, sizeof(array) / sizeof(int), 9);
	return 0;
}
