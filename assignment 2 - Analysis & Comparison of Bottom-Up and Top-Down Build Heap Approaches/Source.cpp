/*
 @author Daniela Teodora Samuil
 @group 30421

   You are required to implement correctly and efficiently two methods for building a heap,
   namely the bottom­up and the top­down strategies. Additionally, you have to implement
   heapsort.


   BottomUp strategy:

   This method starts from the assumption that we already have 2 heaps (1 single node is a really simple heap).
   Thus, we will start from the first non-leaf node (we already know that in a heap, n/2 of the nodes are leaves)
   and we will apply the TopDown (sink the node) such that we will place the current node in its desired place in the heap.
   We continue sinking the nodes until we reach the root of the heap.


   TopDown strategy:

   It takes the elements from the array in order, from left to right, starting with the second one and it compares them 
   with their parent ( parent=(index-1)/2 ) in such a way that they can be arranged to form a heap. If the parent is smaller
   than the element that we are currently comparing it to, we need to switch them and reinitialize the index to be the parent
   and the parent to have a new value, then we repeat this comparison until the property of the heap is satisfied. 
   We start only from the second element because the first one is considered to be its parent (if we would start from the
   first one, there would be no parent for it).


   Conclusions:

   As the demos show, the BottomUp method is quicker than the TopDown method, because we work only with the nodes that are
   not leaves (this will cut the number of nodes to work with in half), whereas in the TopDown strategy we need to compare
   all the nodes with their predecessors in order to form a heap. 

   Running Time: O(n*lgn) ( for all the cases ) 

   - the basic operations on heaps run in time at most proportional to the height of the tree and thus take O(lgn) time
   - the heap has the height of lgn -> heapify runs in O(lgn) + build-heap runs in linear time ( O(n) ) ;  Because each call of
   Heapify costs O(lgn), Build-Heap takes O(n) and it makes n-1 such calls => overall running time is O(n*lgn)
   - Heapify: lets the value at a[i] in an array "float down" in the heap such that the heap maintains its max-heap property ( all the
   children have a smaller value than the parrent ) 
 */


#include <stdlib.h>
#include <stdio.h>

#include "Header.h"

#define AVG_TOPDOWN_ASSIG "average_TopDown_assig"
#define AVG_TOPDOWN_COMP "average_TopDown_comp"
#define AVG_TOPDOWN_OP "average_TopDown_operations"

#define AVG_BOTTOMUP_ASSIG "average_BottomUp_assig"
#define AVG_BOTTOMUP_COMP "average_BottomUp_comp"
#define AVG_BOTTOMUP_OP "average_BottomUp_operations"

Profiler profiler("SortingMethods");

int assig_TopDown, comp_TopDown, assig_BottomUp, comp_BottomUp, Heap_Size;


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


void Heapify(int* a, int n, int index)
{

	int largest = index;

	comp_BottomUp++;
	if (2 * index + 1 < n && a[2 * index + 1] > a[largest])
		largest = 2 * index + 1;


	comp_BottomUp++;
    if (2 * index + 2 < n && a[2 * index + 2] > a[largest])
	largest = 2 * index + 2;


			if (largest != index)
			{
				int aux = a[index];
				a[index] = a[largest];
				a[largest] = aux;

				assig_BottomUp = assig_BottomUp + 3;

				printArray(a, n);

				Heapify(a, n, largest);

			}
}


void BottomUp(int* a, int n)
{
	assig_BottomUp = 0;
	comp_BottomUp = 0;

	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(a, n, i);
}



void HeapSort(int* a, int n)
{
	BottomUp(a, n);
	printf("\n");
	int Heap_Size = n;
	for (int i = n-1; i >= 1; i--)
	{
		int aux = a[0];
		a[0] = a[i];
		a[i] = aux;
		Heap_Size--;
		Heapify(a,Heap_Size, 0);
	}
	printf("\n");
}


void HeapInsert(int* a, int index, int key)
{
	int parent = (index - 1) / 2; //index-1 because we have the indexes starting from 0

		while (a[parent] < a[index])
		{
			comp_TopDown++;

			int aux = a[parent];
			a[parent] = a[index];
			a[index] = aux;
			assig_TopDown = assig_TopDown + 3;

			index = parent;
			parent = (index - 1) / 2;
		}
}


void TopDown(int* a, int n)
{
	assig_TopDown = 0;
	comp_TopDown = 0;

	for (int i = 1; i < n; i++)
	{
		HeapInsert(a,i,a[i]);
		printArray(a, n);
	}
}


void demoTopDown()
{
	printf("Top-Down method\n");

	int a[7] = { 3,7,11,2,12,5,10 };

	printArray(a,7);
	printf("\n\n");
	
	TopDown(a, 7);

	printf("\n");
}


void demoBottomUp()
{
	printf("Bottom-Up method\n");

	int a[7] = { 3,7,11,2,12,5,10 };

	printArray(a, 7);
	printf("\n\n");

		BottomUp(a, 7);
		printf("\n");
}


void demoHeapSort()
{
	printf("HeapSort\n");

	int a[7] = { 3,7,11,2,12,5,10 };

	printArray(a, 7);
	printf("\n\n");

	HeapSort(a, 7);

	printArray(a, 7);
	printf("\n");
}



void generateCharts()
{
	int size;
	int* a;
	int* b;

	for (size = 0; size < 10000; size += 100)
		//avg case: BottomUp
	{
		for (int index = 0; index < 5; index++)
		{
			b = (int*)malloc(size * sizeof(int));
			a = generateAvgData(size);
			for (int i = 0; i < size; i++)
				b[i] = a[i];

			BottomUp(b, size);
			free(b);
		}

		profiler.countOperation(AVG_BOTTOMUP_OP, size, comp_BottomUp/5+ assig_BottomUp / 5);
	}


	for (size = 0; size < 10000; size += 100)
		//avg case: TopDown
	{
		for (int index = 0; index < 5; index++)
		{
			b = (int*)malloc(size * sizeof(int));
			a = generateAvgData(size);
			for (int i = 0; i < size; i++)
				b[i] = a[i];

			TopDown(b, size);
			free(b);
		}

		profiler.countOperation(AVG_TOPDOWN_OP, size, comp_TopDown/5+assig_TopDown/5);
	}


	profiler.createGroup("Average Case Operations", AVG_BOTTOMUP_OP, AVG_TOPDOWN_OP);
}


int main()
{
	demoBottomUp();
	demoHeapSort();
	demoTopDown();

	//generateCharts();

	//profiler.showReport();

	return 0;

}