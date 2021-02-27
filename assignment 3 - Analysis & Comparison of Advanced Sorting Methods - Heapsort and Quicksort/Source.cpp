/*
   @author Daniela Teodora Samuil
   @group 30421

	Quick Sort

	Quick Sort uses the Divide et Impera method. The way this method works is that we take an element as a pivot and
	we compare each element of the array with it ( if it has a smaller or equal value it is going to be placed on the left
	of the pivot, else it is placed on the right side ; this way, the smaller elements than the pivot are going to be on
	one side of the pivot and the bigger elements on the other side ). This is what we call a "Partition". We do this 
	procedure recursevly, until all the array is sorted.

	Complexity(it depends if the partition is balanced or unbalanced):

	Best: O(nlgn) (the best case occurs when the pivot is taken as the middle element of the array)
	Average: O(nlgn) (the partition produces a mix of "good" and "bad" splits ; the good & bad splits are distributed randomly
	throughout the recursion tree )
	Worst: O(n^2) (when the partitioning is made into an (n-1) array and a single element array; moreover, when the array
	is already completely sorted)


	-A randomized version of quicksort: we will select a randomly chosen element from the given array and exchange it with 
	the last element -> this ensures that the pivot element is equally likely to be any of the elements of the array ; because
	we randomly choose the pivot, we expect the split to be well balanced. -> the running time of a quicksort using randomized
	partition is going to be O(n*lgn)

	HeapSort

	First, we need to build the heap and for that we use the BottomUp method, because it shortens the running time (it works
	only with the nodes that are non-leaves). After the heap is built, we will interchange the first element ( which is the
	root of the heap => the biggest value ) with the last element, and so, in doing that, we assure that the element is in
	its final place in the array. Because we swaped elements, the heap ( which now has a new lenght, original lenght -1) 
	is no longer valid, so we need to use Heapify method ( sinking the root of the new heap until its place and then repeating
	the procedure) in order to form the heap again. We repeat the interchanging method and heapify until we have the array 
	sorted.

	*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Header.h"

Profiler profiler("QuickSort");

#define AVG_QUICKSORTRAND_OP "average_QuickSort_operations"
#define AVG_HEAPSORT_OP "average_HeapSort_operations"
#define BEST_QUICKSORT_OP "best_QuickSort_operations"
#define WORST_QUICKSORT_OP "worst_QuickSort_operations"
#define BEST_QUICKSORTRAND_OP "best_QuickSort_operations"
#define WORST_QUICKSORTRAND_OP "worst_QuickSort_operations"
#define AVG_QUICKSORT_OP "average_QuickSort_operations"


int assig_QuickSort, comp_QuickSort, assig_HeapSort, comp_HeapSort, totalOperations_QuickSort, totalOperations_HeapSort;



void printArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);

	printf("\n");
}


int* generateAvgData(int n)
{
	int* a = (int*)malloc(n * sizeof(int));

	FillRandomArray(a, n);

	return a;

}


int* generateAscendingOrderArray(int n)
{
	int* a = (int*)malloc(n * sizeof(int));

	FillRandomArray(a, n, 10, 5000, false, 1);

	return a;
}


int Partition(int* a, int n, int p, int r, bool m)
{
	int aux;

	int x = a[r];
	int i = p-1 ;

	for (int j = p; j <= r - 1; j++)
	{
		comp_QuickSort++;

		if (a[j] <= x)
		{
			i++;
			aux = a[i];
			a[i] = a[j];
			a[j] = aux;
			assig_QuickSort = assig_QuickSort + 3;
		}
	}
	aux = a[i + 1];
	a[i+1] = a[r];
	a[r] = aux;
	assig_QuickSort = assig_QuickSort + 3;

	if (m)
	{
		printf("index for partition:%d     ", i + 1);
	}

	return i + 1;
}

int Random(int a, int b)
{
	srand(time(NULL));
	return a + rand() % (b - a);
}


int RandomizedPartition(int* a,int n, int p, int r,bool m)
{
	int i = Random(p, r);
	int aux = a[r];
	a[r] = a[i];
	a[i] = aux;
	assig_QuickSort = assig_QuickSort + 3;
	return Partition(a,n, p, r,m);
}


void QuickSort(int* a, int n, int p, int r, bool m)
{

	if (p < r)
	{
		int q = Partition(a, n, p, r,m);

		if (m)
		{
			printArray(a, n);
		}

		QuickSort(a, n, p, q - 1,m);

		QuickSort(a, n, q + 1, r,m);
	}

}


void RandomizedQuickSort(int*a,int n, int p, int r,bool m)
{

	if (p< r)
	{
		int q = RandomizedPartition(a,n, p, r,m);

		if (m)
		{
			printArray(a, n);
		}

		RandomizedQuickSort(a,n, p, q-1,m);
		RandomizedQuickSort(a,n, q + 1, r,m);
	}
}

void Heapify(int* a, int n, int index, bool m)
{

	int largest = index;

	comp_HeapSort++;
	if (2 * index + 1 < n && a[2 * index + 1] > a[largest])
		largest = 2 * index + 1;

	comp_HeapSort++;
	if (2 * index + 2 < n && a[2 * index + 2] > a[largest])
		largest = 2 * index + 2;


	if (largest != index)
	{
		int aux = a[index];
		a[index] = a[largest];
		a[largest] = aux;

		assig_HeapSort = assig_HeapSort + 3;

		if (m)
		{
			printArray(a, n);
		}

		Heapify(a, n, largest,m);

	}
}


void BottomUp(int* a, int n,bool m)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(a, n, i,m);
}



void HeapSort(int* a, int n,bool m)
{
	BottomUp(a, n,m);
	printf("\n");
	int Heap_Size = n;
	for (int i = n - 1; i >= 1; i--)
	{
		if (m)
		{
			printf("Element placed in the final array: %d\n", a[0]);
		}

		int aux = a[0];
		a[0] = a[i];
		a[i] = aux;

		assig_HeapSort = assig_HeapSort + 3;

		Heap_Size--;
		Heapify(a, Heap_Size, 0,m);
	}
	printf("\n\n");
}


int QuickSelect(int* a,int n, int p, int r, int i,bool m)
{
	if (p == r)
		return a[p];

	int q = RandomizedPartition(a,n, p, r,m);

	if (m)
	{
		printArray(a, n);
	}

	int k = q - p + 1;

	if (i == k)
		return a[q];
	else if (i<k)
		return QuickSelect(a, n, p, q - 1, i, m);
	else return QuickSelect(a, n, q + 1, r, i - k, m);

}


void demoQuickSort()
{
	printf("QuickSort demo\n");

	int a[9] = { 3,7,11,2,12,5,10,9,8 };

	printArray(a, 9);
	printf("\n\n");

	QuickSort(a, 9, 0,8,true);


	printf("\n");
}

void demoRandQuickSort()
{
	printf("Randomized QuickSort demo\n");

	int a[9] = { 3,7,11,2,12,5,10,9,8 };

	printArray(a, 9);
	printf("\n\n");

	RandomizedQuickSort(a, 9, 0, 8, true);

	printf("\n");
}


void demoQuickSelect()
{
	printf("QuickSelect demo\n");

	int a[9] = { 3,7,11,2,12,5,10,9,8 };

	printArray(a, 9);
	printf("\n\n");

	int x = QuickSelect(a, 9, 0, 8, 6, true);

	printf("Element: %d", x);

	printf("\n");
}

void demoHeapSort()
{
	printf("HeapSort demo\n");

	int a[9] = { 3,7,11,2,12,5,10,9,8 };

	printArray(a, 9);
	printf("\n\n");

	HeapSort(a, 9,true);

	printArray(a, 9);

	printf("\n");
}




void generateCharts()
{
	int size;
	int* a;
	int* b;

	for (size = 1; size < 10001; size += 100)
		//avg case: QuickSort & HeapSort
	{
		totalOperations_QuickSort=0; 
		totalOperations_HeapSort = 0;

		for (int index = 0; index < 5; index++)
		{
			b = (int*)malloc(size * sizeof(int));
			a = generateAvgData(size);

			assig_HeapSort = 0;
			comp_HeapSort = 0;
			assig_QuickSort = 0;
			comp_QuickSort = 0;

			for (int i = 0; i < size; i++)
				b[i] = a[i];
			
			HeapSort(b, size, false);


			for (int i = 0; i < size; i++)
				b[i] = a[i];

			RandomizedQuickSort(b, size, 0, size - 1, false);

			free(b);

			totalOperations_HeapSort = totalOperations_HeapSort + assig_HeapSort + comp_HeapSort;
			totalOperations_QuickSort = totalOperations_QuickSort + assig_QuickSort + comp_QuickSort;
		}

		profiler.countOperation(AVG_QUICKSORTRAND_OP, size, totalOperations_QuickSort / 5);
		profiler.countOperation(AVG_HEAPSORT_OP, size, totalOperations_HeapSort / 5);
	}


	for (size = 1; size < 10001; size += 100)
	{	//QuickSort-randomized: Best 

		totalOperations_QuickSort = 0;

			a = generateAvgData(size);

			assig_QuickSort = 0;
			comp_QuickSort = 0;

			RandomizedQuickSort(a, size, 0, size - 1, false);

			totalOperations_QuickSort = totalOperations_QuickSort + assig_QuickSort + comp_QuickSort;
		profiler.countOperation(BEST_QUICKSORTRAND_OP, size, totalOperations_QuickSort / 5);
	}

	for (size = 1; size < 10001; size += 100)
	{	//QuickSort-randomized: Worst (when the array is already sorted)

		totalOperations_QuickSort = 0;

			a = generateAscendingOrderArray(size);

			assig_QuickSort = 0;
			comp_QuickSort = 0;

			RandomizedQuickSort(a, size, 0, size - 1, false);

			totalOperations_QuickSort = totalOperations_QuickSort + assig_QuickSort + comp_QuickSort;

		profiler.countOperation(WORST_QUICKSORTRAND_OP, size, totalOperations_QuickSort / 5);
	}


	for (size = 1; size < 10001; size += 100)
	{	//QuickSort: Average

		totalOperations_QuickSort = 0;

		for (int index = 0; index < 5; index++)
		{
			b = (int*)malloc(size * sizeof(int));
			a = generateAvgData(size);

			assig_QuickSort = 0;
			comp_QuickSort = 0;

			for (int i = 0; i < size; i++)
				b[i] = a[i];

			QuickSort(b, size, 0, size - 1, false);

			free(b);

			totalOperations_QuickSort = totalOperations_QuickSort + assig_QuickSort + comp_QuickSort;
		}
		profiler.countOperation(AVG_QUICKSORT_OP, size, totalOperations_QuickSort / 5);
	}

	for (size = 1; size < 10001; size += 100)
	{	//QuickSort: Best 

		totalOperations_QuickSort = 0;

			a = generateAvgData(size);

			assig_QuickSort = 0;
			comp_QuickSort = 0;

			QuickSort(a, size, 0, size - 1, false);

			totalOperations_QuickSort = totalOperations_QuickSort + assig_QuickSort + comp_QuickSort;

		profiler.countOperation(BEST_QUICKSORT_OP, size, totalOperations_QuickSort / 5);
	}


	for (size = 1; size < 10001; size += 100)
	{	//QuickSort: Worst (when the array is already sorted)

		totalOperations_QuickSort = 0;

			a = generateAscendingOrderArray(size);

			assig_QuickSort = 0;
			comp_QuickSort = 0;

			QuickSort(b, size, 0, size - 1, false);
			
			totalOperations_QuickSort = totalOperations_QuickSort + assig_QuickSort + comp_QuickSort;

		profiler.countOperation(WORST_QUICKSORT_OP, size, totalOperations_QuickSort / 5);
	}

	profiler.createGroup("Average Case", AVG_QUICKSORTRAND_OP, AVG_HEAPSORT_OP);
	profiler.createGroup("QuickSort-RandomizedPartition", WORST_QUICKSORTRAND_OP, BEST_QUICKSORTRAND_OP);
	profiler.createGroup("QuickSort", BEST_QUICKSORT_OP, WORST_QUICKSORT_OP);
	profiler.createGroup("Average QuickSort", AVG_HEAPSORT_OP);
	profiler.createGroup("Average QuickSortRand", AVG_QUICKSORTRAND_OP);
}



int main()
{
	demoQuickSort();
	demoHeapSort();
	demoRandQuickSort();
	demoQuickSelect();

	generateCharts();

	profiler.showReport();

	return 0;
}