#include <stdio.h>

void insert_sort(int array[], int len)
{
	for (int i = 1; i < len; i++) {// i: 代表即将插入的元素角标,作为每一组比较数据的最后一个元素
		for (int j = i; j > 0; j--) {   //j:代表数组角标
			if (array[j] < array[j - 1]) {//符合条件，插入元素（交换位置）
				int temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
			}
		}
	}
}

void insert_sort2(int array[], int len)
{
	int tmp, tmpi;

	for (int i = 1; i < len; i++) {
		tmpi = i;
		for (int j = tmpi - 1; j >=0 ; j--) {
			if (array[j] > array[tmpi]) {
				tmp = array[j];
				array[j] = array[tmpi];
				array[tmpi] = tmp;
				tmpi--;
			}
		}
	}
}

void insert_sort3(int arr[], int len){
	int i,j,key;

	for (i=1;i < len; i++){
		key = arr[i];
		j=i-1;
		while((j>=0) && (arr[j]>key)) {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}

void quicksort(int R[], int lo, int hi){
    int i = lo, j = hi;
    int temp;
    if(i < j){
        temp = R[i];
        while (i != j)
        {
            while(j > i && R[j] > temp)-- j;
            R[i] = R[j];
            while(i < j && R[i] < temp)++ i;
            R[j] = R[i];
        }
        R[i] = temp;
        QuickSort(R, lo, i - 1);
        QuickSort(R, i + 1, hi);
    }
}

int main(int argc, char *argv[])
{
	int array[] = {15, 14, 16, 17, 19, 18};

	for (int i = 0; i < 6; ++i) {
		printf("%d ", array[i]);
	}

	printf("\n");

	insert_sort3(array, 6);


	for (int i = 0; i < 6; ++i) {
		printf("%d ", array[i]);
	}

	printf("\n");

	return 0;
}
