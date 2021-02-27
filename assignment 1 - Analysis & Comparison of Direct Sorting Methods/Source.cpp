/*
 @author Daniela Teodora Samuil
 @group 30421
 
You are required to implement correctly and efficiently 3 direct sorting methods (Bubble Sort,
Insertion Sort – using either linear or binary insertion and Selection Sort)
 
  Bubble Sort Algorithm:s

  It sorts an array using 2 "for" loops, comparing pairs of elements, starting to build the array from the biggest
  element to the smallest (from right to left) using swaps. The second loop stops at the n-i-1 element, since the array
  is going to be already sorted from that point onwards.

  Complexity:
  Worst - O(n^2)
  Average - O(n^2)
  Best - O(n^2)

  Stability:
  The algorithm is stable because we take the elements in order from left to right and the comparison is done with the
  "strictly greater than", which will ensure the correct position of the duplicates.

  Insertion Sort Algorithm:

  It sorts the array taking the first element that is unsorted, besides the very first element, (pivot) and comparing it
  with all the elements before it (from right to left) , and if one of them is bigger than the pivot, we shift all the 
  elements from that found position onwards to the right with one position and we put the pivot in place of the value 
  that we initially found as being bigger. We repeat this process until the pivot has been compared with all the elements 
  before it. We can visualise this as picking an element from an unsorted array and placing it where it belongs into a 
  sorted array.

  Complexity:
  Worst - O(n^2)
  Average - O(n^2)
  Best - O(n)

  Stability:
  The algorithm is stable because the elements from the unsorted sequence are being taken in order and because we have the
  "strictly greater than" condition into the "while" loop, we are going to sort the duplicates in the right order.


  Selection Sort Algorithm:

  We sort the array using an index which will keep the position of the smallest element from the unsorted array, starting
  with the second element (like the Insertion Method, we can say that we wil have 2 arrays, one ordered (left) and one 
  unordered (right), and we take the most convenient element from the unordered array and swap it with either the element
  on the first position of the unordered array (if the last element of the sorted array is smaller than the element indicated
  by the index) or with the last element of the sorted array (in the opposite case).

  Complexity:
  Worst - O(n^2)
  Average - O(n^2)
  Best - O(n)

  Stability:
  We can not say anything about the stability.


  As a conclusion, we can observe that the complexity regarding the worst case is the same for all the 3 sorting methods,
  whereas, for the best case scenario, the Insertion and Selection methods are better than the Bubble Sort Method, both
  having the running time equal with O(n).
 */


#include <stdlib.h>
#include <stdio.h>

#include "Header.h"

#define AVG_BUBBLE_COMP "avg_bubble_comp"
#define AVG_BUBBLE_ASSIG "avg_bubble_assig"
#define AVG_BUBBLE_OP "avg_bubble_operations"

#define AVG_INSERTION_COMP "avg_insertion_comp"
#define AVG_INSERTION_ASSIG "avg_insertion_assig"
#define AVG_INSERTION_OP "avg_insertion_operations"

#define AVG_SELECTION_COMP "avg_selection_comp"
#define AVG_SELECTION_ASSIG "avg_selection_assig"
#define AVG_SELECTION_OP "avg_selection_operations"

#define BEST_BUBBLE_COMP "best_bubble_comp"
#define BEST_BUBBLE_ASSIG "best_bubble_assig"
#define BEST_BUBBLE_OP "best_bubble_operations"

#define BEST_INSERTION_COMP "best_insertion_comp"
#define BEST_INSERTION_ASSIG "best_insertion_assig"
#define BEST_INSERTION_OP "best_insertion_operations"

#define BEST_SELECTION_COMP "best_selection_comp"
#define BEST_SELECTION_ASSIG "best_selection_assig"
#define BEST_SELECTION_OP "best_selection_operations"

#define WORST_BUBBLE_COMP "worst_bubble_comp"
#define WORST_BUBBLE_ASSIG "worst_bubble_assig"
#define WORST_BUBBLE_OP "worst_bubble_operations"

#define WORST_INSERTION_COMP "worst_insertion_comp"
#define WORST_INSERTION_ASSIG "worst_insertion_assig"
#define WORST_INSERTION_OP "worst_insertion_operations"

#define WORST_SELECTION_COMP "worst_selection_comp"
#define WORST_SELECTION_ASSIG "worst_selection_assig"
#define WORST_SELECTION_OP "worst_selection_operations"


Profiler profiler("SortingMethods1");

int assig_bubble, comp_bubble, assig_insertion, comp_insertion, assig_selection, comp_selection;


void printArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);

	printf("\n");
}


void BubbleSort(int* a, int n)
{
	assig_bubble = 0;
	comp_bubble = 0;

	for(int i = 0; i<n-1; i++)
		for (int j = 0; j<n-i-1; j++)
		{
			if (a[j] > a[j + 1])
			{
				int aux = a[j];
				a[j] = a[j + 1];
				a[j + 1] = aux;
				assig_bubble = assig_bubble + 3;
				printArray(a, n);
			}
			comp_bubble++;
		}
}

void InsertionSort(int* a, int n)
{
	assig_insertion = 0;
	comp_insertion = 0;

	for (int i = 1; i < n; i++)
	{
		int pivot = a[i];
		assig_insertion++;
		int j = i - 1;
		while (j >= 0 && a[j] > pivot)
		{
			comp_insertion++;
			a[j + 1] = a[j];
			assig_insertion++;
			j--;
		}
		a[j + 1] = pivot;
		printArray(a, n);
		assig_insertion++;
	}

}

void SelectionSort(int* a, int n)
{
	assig_selection = 0;
	comp_selection = 0;

	int aux;

	for (int i = 0; i < n-1; i++)
	{
		int index = i + 1;
		for (int j = i + 2; j < n; j++)
			if (a[index] > a[j])
				index = j;
		comp_selection++;
		if (a[i] < a[index])
		{
			aux = a[i + 1];
			a[i + 1] = a[index];
			a[index] = aux;
			printArray(a, n);
			assig_selection = assig_selection + 3;
		}
		else
		{
			aux = a[i];
			a[i] = a[index];
			a[index] = aux;
			printArray(a, n);
			assig_selection = assig_selection + 3;
		}
		comp_selection++;
	}
}



void demoBubble()
{
	printf("Demo Bubble\n");

	int a[5] = { 3,7,11,2,12 };

	printArray(a, 5);
	printf("\n");
	printf("\n");
	BubbleSort(a, 5);
	printf("\n");
}

void demoInsertion()
{
	printf("Demo Insertion\n");

	int a[5] = { 3,7,11,2,12 };

	printArray(a, 5);
	printf("\n");
	printf("\n");
	InsertionSort(a, 5);
	printf("\n");
}

void demoSelection()
{
	printf("Demo Selection\n");

	int a[5] = { 3,7,11,2,12 };

	printArray(a, 5);
	printf("\n");
	printf("\n");
	SelectionSort(a, 5);
	printf("\n");
}


int* generateAvgData(int n)
	{
		int*a = (int*)malloc(n * sizeof(int));
		
		FillRandomArray(a, n);

		return a;

	}

int* generateAscendingOrderArray(int n)
{
	int* a = (int*)malloc(n * sizeof(int));

	FillRandomArray(a, n, 10, 5000, false, 1);

	return a;
}

int* generateDescendingOrderArray(int n)
{
	int* a = (int*)malloc(n * sizeof(int));

	FillRandomArray(a, n, 10, 5000, false, 2);

	return a;
}


void generateCharts()
{
	int size;
	int* a;
	int* b;

	for (size = 0; size < 10000; size += 100)
		//avg case: Bubble
	{
		for (int index = 0; index < 5; index++)
		{
			a = generateAvgData(size);
			b = (int*)malloc(size * sizeof(int));
			for (int i = 0; i < size; i++)
				b[i] = a[i];

			BubbleSort(b, size);
			free(b);

		}

		profiler.countOperation(AVG_BUBBLE_COMP, size, comp_bubble/5);
		profiler.countOperation(AVG_BUBBLE_ASSIG, size, assig_bubble/5);
	}
	profiler.addSeries(AVG_BUBBLE_OP, AVG_BUBBLE_COMP, AVG_BUBBLE_ASSIG);

	for (size = 0; size < 10000; size += 100)
		//avg case: Insertion
	{
		for (int index = 0; index < 5; index++)
		{
			a = generateAvgData(size);
			b = (int*)malloc(size * sizeof(int));
			for (int i = 0; i < size; i++)
				b[i] = a[i];

			InsertionSort(b, size);
			free(b);
		}

		profiler.countOperation(AVG_INSERTION_COMP, size, comp_insertion/5);
		profiler.countOperation(AVG_INSERTION_ASSIG, size, assig_insertion/5);
	}
	profiler.addSeries(AVG_INSERTION_OP, AVG_INSERTION_COMP, AVG_INSERTION_ASSIG);

	for (size = 0; size < 10000; size += 100)
		//avg case: Selection
	{
		for (int index = 0; index < 5; index++)
		{
			a = generateAvgData(size);
			b = (int*)malloc(size * sizeof(int));
			for (int i = 0; i < size; i++)
				b[i] = a[i];

			SelectionSort(b, size);
			free(b);
		}

		profiler.countOperation(AVG_SELECTION_COMP, size, comp_selection/5);
		profiler.countOperation(AVG_SELECTION_ASSIG, size, assig_selection/5);
	}
	profiler.addSeries(AVG_SELECTION_OP, AVG_SELECTION_COMP, AVG_SELECTION_ASSIG);




	for (size = 0; size < 10000; size += 100)
		//best case: Bubble
	{
		a = generateAscendingOrderArray(size);
		BubbleSort(a, size);

		free(a);

		profiler.countOperation(BEST_BUBBLE_COMP, size, comp_bubble);
		profiler.countOperation(BEST_BUBBLE_ASSIG, size, assig_bubble);
	}
	profiler.addSeries(BEST_BUBBLE_OP, BEST_BUBBLE_COMP, BEST_BUBBLE_ASSIG);

	for (size = 0; size < 10000; size += 100)
		//best case: Insertion
	{
		a = generateAscendingOrderArray(size);
		InsertionSort(a, size);

		free(a);

		profiler.countOperation(BEST_INSERTION_COMP, size, comp_insertion);
		profiler.countOperation(BEST_INSERTION_ASSIG, size, assig_insertion);
	}
	profiler.addSeries(BEST_INSERTION_OP, BEST_INSERTION_COMP, BEST_INSERTION_ASSIG);

	for (size = 0; size < 10000; size += 100)
		//best case: Selection
	{
		a = generateAscendingOrderArray(size);
		SelectionSort(a, size);

		free(a);

		profiler.countOperation(BEST_SELECTION_COMP, size, comp_selection);
		profiler.countOperation(BEST_SELECTION_ASSIG, size, assig_selection);
	}
	profiler.addSeries(BEST_SELECTION_OP, BEST_SELECTION_COMP, BEST_SELECTION_ASSIG);




	for (size = 0; size < 10000; size += 100)
		//worst case: Bubble
	{
		a = generateDescendingOrderArray(size);
		BubbleSort(a, size);

		free(a);

		profiler.countOperation(WORST_BUBBLE_COMP, size, comp_bubble);
		profiler.countOperation(WORST_BUBBLE_ASSIG, size, assig_bubble);
	}
	profiler.addSeries(WORST_BUBBLE_OP, WORST_BUBBLE_COMP, WORST_BUBBLE_ASSIG);

	for (size = 0; size < 10000; size += 100)
		//worst case: Insertion
	{
		a = generateDescendingOrderArray(size);
		InsertionSort(a, size);

		free(a);

		profiler.countOperation(WORST_INSERTION_COMP, size, comp_insertion);
		profiler.countOperation(WORST_INSERTION_ASSIG, size, assig_insertion);
	}
	profiler.addSeries(WORST_INSERTION_OP, WORST_INSERTION_COMP, WORST_INSERTION_ASSIG);

	for (size = 0; size < 10000; size += 100)
		//worst case: Selection
	{
		a = generateDescendingOrderArray(size);
		SelectionSort(a, size);

		free(a);

		profiler.countOperation(WORST_SELECTION_COMP, size, comp_selection);
		profiler.countOperation(WORST_SELECTION_ASSIG, size, assig_selection);
	}
	profiler.addSeries(WORST_SELECTION_OP, WORST_SELECTION_COMP, WORST_SELECTION_ASSIG);

	profiler.createGroup("Average Case Operations", AVG_BUBBLE_OP, AVG_SELECTION_OP, AVG_INSERTION_OP);
	profiler.createGroup("Average Case Assignments", AVG_BUBBLE_ASSIG, AVG_SELECTION_ASSIG, AVG_INSERTION_ASSIG);
	profiler.createGroup("Average Case Comparisons", AVG_BUBBLE_COMP, AVG_SELECTION_COMP, AVG_INSERTION_COMP);

	profiler.createGroup("Best Case Operations", BEST_BUBBLE_OP, BEST_SELECTION_OP);
	profiler.createGroup("Best Case Assignments", BEST_BUBBLE_ASSIG, BEST_SELECTION_ASSIG, BEST_INSERTION_ASSIG);
	profiler.createGroup("Best Case Comparisons", BEST_BUBBLE_COMP, BEST_SELECTION_COMP);

	profiler.createGroup("Worst Case Operations", WORST_BUBBLE_OP, WORST_SELECTION_OP, WORST_INSERTION_OP);
	profiler.createGroup("Worst Case Assignments", WORST_BUBBLE_ASSIG, WORST_SELECTION_ASSIG, WORST_INSERTION_ASSIG);
	profiler.createGroup("Worst Case Comparisons", WORST_BUBBLE_COMP, WORST_SELECTION_COMP);
}

int main()
{
	demoBubble();
	demoInsertion();
	demoSelection();

	//generateCharts();

	//profiler.showReport();

	return 0;
}