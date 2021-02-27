/*
   @author Daniela Teodora Samuil
   @group 30421

   You are required to implement correctly and efficiently an O(nlogk) method for merging k sorted sequences, 
   where n is the total number of elements.


   For solving this problem, we adapted the heap to a min-HEAP structure, because we will need to have the smallest 
   element on the first position (root), as we will use it and insert it in the final list. The "heapify" function is 
   also changed, ajusted in such a way that we work with lists as the nodes ( we basically use heapify on the first 
   element of each of the k lists we have, and we can say that we have a heap formed by the first element of all the lists)
   After choosing the element that we want to insert into our final list(root of the heap), we will delete it and assign its
   place (as first element) to the one that is following it (DeleteFirst in a linked list) & we will use heapify for the new
   structure we have. When all the elements from a list have been deleted, we reduce the lenght of the heap so we
   can repeat the procedure. When, at last, we have only 2 lists left ( one being the large final list and one being one
   the initial lists ) we will use the Merge2 function, which simply merges two lists.

   -to search in a list of n object it takes O(n) time in the WORST case, since we may have to search the whole list.
   -list insertion takes O(1), delete runs in O(1) as well.
   -since it takes O(logk) for using heapify when we have k elements (because we put in the heap only the first elements of the sorted
   array and we have k arrays => k elements for the heap) and in the worst case searching for the next smallest element is
   O(n) => O(n*logk)
   	*/


#include <stdlib.h>
#include <stdio.h>

#include "Header.h"

Profiler profiler("LinkedLists");

int number_OPERATIONS;

#define COUNT1 "N FIXED, VARY K"
#define COUNT2 "K FIXED, VARY N"

struct node 
{
	int value;
	struct node* next;
};


typedef struct
{
	node* first;
	node* last;
	int length;
} List;



node* CreateNode(int k)
{
	node* p = (node*)malloc(sizeof(node));
	if(p)
	{
		p->value = k; 
		p->next = NULL;
	}
	return p;
}



void CreateEmptyList(List* a)
{
		a->length = 0;
		a->first = a->last = NULL;
}



int IsEmpty(List* a)
{
	if (a->first == NULL)
		return 1;
	else return 0;
}


void InsertAtRear(List* a, int key)
{
	node* p = CreateNode(key);

	
		if (IsEmpty(a))
		{
			a->first = p;
			a->last = p;
		}

		else
		{
			a->last->next = p;
			a->last = p;

		}
		
		a->length++;


}


void DeleteFirst(List* a)
{
	node* p = (node*)malloc(sizeof(node));

	if(IsEmpty(a)==0)
	{
			p= a->first;
		    a->first = a->first->next;
      
			free(p); 

		a->length--; 
		
		if(a->first == NULL) 
			a->last = NULL;
		
	}
}


void PrintList(List* a)
{
	node* p;

	p = a->first;

	while (p != NULL) 
	{
		printf("%d ", p->value);
		p = p->next;
	}
	printf("\n");

	free(p);
}


void PrintArrayOfLists(List* list[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("List %d :  ", i);
		PrintList(list[i]);
		printf("\n");
	}
	printf("\n");
}


void BuildAList(List* list,int n)
{
	int* a = (int*)malloc(n*sizeof(int));
	
	FillRandomArray(a, n, 1, 50, false, 1);

	CreateEmptyList(list);

	for (int i = 0; i < n; i++)
		InsertAtRear(list, a[i]);


	free(a);
}


void BuildAllLists(List* list[],int n,int k)
{
	int m = n / k;

	for (int i = 0; i < k; i++) {
		list[i] = (List*)malloc(sizeof(List));
		BuildAList(list[i], m);
	}

}



void mergeTwoLists(List* m, List* n, List* p)
{
	node* a = (node*)malloc(sizeof(node));
	node* b = (node*)malloc(sizeof(node));

	a = m->first;
	b = n->first;

	number_OPERATIONS += 2;

	while (a != NULL && b != NULL)
	{
		number_OPERATIONS++;
		if (a->value < b->value)
		{
			InsertAtRear(p, a->value);
			a = a->next;
			number_OPERATIONS++;
		}
		else
		{
			number_OPERATIONS++;
			if (a->value > b->value)
			{
				InsertAtRear(p, b->value);
				b = b->next;
				number_OPERATIONS++;
			}
			else
			{
				InsertAtRear(p, a->value);
				InsertAtRear(p, b->value);
				a = a->next;
				b = b->next;
				number_OPERATIONS += 2;
			}
		}

	} 
	number_OPERATIONS += 2;

	while (a != NULL)
	{
		InsertAtRear(p, a->value);
		a = a->next;

		number_OPERATIONS ++;
	}
	number_OPERATIONS++;

	while (b != NULL)
	{
		InsertAtRear(p, b->value);
		b = b->next;

		number_OPERATIONS ++;
	}
	number_OPERATIONS++;

	free(a);
	free(b);
}




void Heapify(List* a[], int n, int index)
{

	int smallest = index;

	number_OPERATIONS++;
	if (2 * index + 1 < n && a[2 * index + 1]->first->value < a[smallest]->first->value)
		smallest = 2 * index + 1;


	number_OPERATIONS++;
	if (2 * index + 2 < n && a[2 * index + 2]->first->value < a[smallest]->first->value)
		smallest = 2 * index + 2;

	//vede care din liste are primul el cel mai mic

	if (smallest != index)
	{
		List* aux = a[index];
		a[index] = a[smallest];
		a[smallest] = aux;

		number_OPERATIONS += 3;

		Heapify(a, n, smallest);

	}

	//lista 0 o sa aiba cel mai mic element primul dupa operatii
}


void BottomUp(List* a[], int n)
{

	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(a, n, i);
}



void MergekLists(List* a[], int k, List* p,bool x)
{
	int heapsize = k;

	CreateEmptyList(p);

	BottomUp(a, k);

	if (x)
	{
		printf("After the heap is created:\n");
		PrintArrayOfLists(a, k);
	}

	while(heapsize>=3)
	{
		InsertAtRear(p, a[0]->first->value);

		DeleteFirst(a[0]);

		if (IsEmpty(a[0]))
		{
			a[0] = a[heapsize-1];
			number_OPERATIONS++;
			heapsize--;
		}


		Heapify(a, heapsize, 0);

		if (x)
		{
			printf("After we insert the chosen element into the final list & heapify:\n");
			PrintArrayOfLists(a, k);
		}
	}
	
	mergeTwoLists(a[0], a[1], p);



}



void demoGenerateLists()
{
	int n = 20;
	int k = 4;

	List* p[100];

	BuildAllLists(p, n, k);

	PrintArrayOfLists(p,k);

	printf("\n");
}


void demoMerge2()
{
	int n = 7;
	List* p = (List*)malloc(sizeof(List));
	List* a = (List*)malloc(sizeof(List));
	List* b = (List*)malloc(sizeof(List));

	BuildAList(a, n);

	printf("First list is: ");
	PrintList(a);
	printf("\n");

	BuildAList(b, n);

	printf("Second list is: ");
	PrintList(b);
	printf("\n");

	CreateEmptyList(p);
	mergeTwoLists(a, b, p);

	printf("Final list is: ");
	PrintList(p);

	printf("\n\n");
}


void demoMergek()
{
	int k = 4;
	
	List* m[100];
	List* p = (List*)malloc(sizeof(List));

	MergekLists(m, k, p,true);

	printf("Final list:\n");
	PrintList(p);
}


void VaryN(List* a[], List* p, int k)
{
	int n;

	number_OPERATIONS = 0;

	char string[100];

	sprintf_s(string,"k_%d", k);

	CreateEmptyList(p);

	for (n = 100; n <= 10000; n = n + 100)
	{

		BuildAllLists(a, n, k);
		MergekLists(a, k, p,false);

		profiler.countOperation(string, n, number_OPERATIONS);
	}
}


void VaryK(List* a[], List* p, int n)
{
	int k;

	number_OPERATIONS = 0;

	CreateEmptyList(p);

	for (k = 10; k <= 500; k = k + 10)
	{
		BuildAllLists(a, n, k);
		MergekLists(a, k, p,false);

		profiler.countOperation(COUNT1, k, number_OPERATIONS);
	}
}


void GenerateGraphs()
{
	List* p= (List*)malloc(sizeof(List));
	List* a[5000];

	VaryN(a, p, 5);
	VaryN(a, p, 10); 
	VaryN(a, p, 15);

	profiler.createGroup(COUNT2, "k_5", "k_10", "k_15");

	VaryK(a, p, 10000);


}


int main()
{
	printf("Generating 4 sorted lists:\n\n");
	demoGenerateLists();

	printf("Merging 2 lists:\n\n");
	demoMerge2();
	printf("\n");

	printf("Merge k(=4) lists:\n\n");
	demoMergek();

	GenerateGraphs();

	profiler.showReport();

	return 0;
}