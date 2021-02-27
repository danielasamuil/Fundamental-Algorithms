/*
   @author Daniela Teodora Samuil
   @group 30421


  You are required to implement correctly and efficiently the base operations for disjoint set
  and the Kruskal’s algorithm using disjoint sets.  You have to use a tree as the representation of 
  a disjoint set. Each tree holds, besides the necessary information, also the rank field (i.e. 
  the height of the tree).


   We will create a set having only one element (rank=0) and we will make it such that the parent
   of the node in the set will be the node itself (each node will have as representative itself)(this is MAKE-SET) ->
   We spend O(n) time to make n sets ( O(1) to make one set )

   For the searching part (FIND_SET) we will compare the node with its parent and if they are different we 
   will call recursevly the function on its parent (the purpose of this function is to find the representative
   of a set). -> complexity depends on how UNION is implemented
   
   As for the UNION part, we will first make a function that unites two nodes into a set, then we will
   use that function together with the FIND one to make sure we can make a union between disjoint sets(using the
   representative/parent). When we call the union function, it first compares the ranks of the two nodes(because
   we need union by rank) and is the first one is bigger, the parent of the second one will take the value of
   the first node, else, the parent of the first node will take the value of the second node. If the ranks were
   equal, we need to make the rank of the new set bigger with one unit (else it remains the same because we look
   at the set like a tree and rank is the height; union will add to the root). 
   ->Using path compression alone gives a worst-case running time of (theta)(n+f*(1+log((baza)2+f/n)n)), for a sequence of n 
   MakeSet operations (and hence at most n-1 Union operations) and f Find operations.
   ->Using union by rank alone gives a running-time of O(m*log(2)n) for m operations of any sort of which n are MakeSet operations.
   ->Using both path compression and union by rank is only O((alpha)(n)) which is optimal (alpha)(n) has a value <5, so the disjoint-set 
   operations take place in essentially constant time.


   To apply Kruskal's algorithm, we firstly need to generate random edges between the nodes that we already have.
   For the first n-1 edges (the ones that make a complete graph between our nodes) we will assign a random value
   using the indexes i & i+1 from an array going from 0 to n-2 (where n=nr of nodes). For the rest of the edges
   we will use random generated arrays(for node1, node2 and weight), and an array going from n-1 to 4*n-1:
   each edge will take a value from the random generated array based on i-(n-1) (this way we take the value
   in the random array beggining with the first one and moving along). We then use a sorting algorithm that
   takes the first index of the array and makes it the index of the minimum value and then using a bubble sort
   strategy we go through the array and when we find another element smaller than the element at the min index
   we swap them -> we will have a sorted array of weights. The actual implementation of the Kruskal's algorithm
   goes as it follows: for each index from 0 to 4*n-1 it compares the sets that contain the nodes that 
   constitute the ith edge in the ordered array of edges. If they are different (not in the same set), we will
   store the nodes values into a new allocate array of type edge* into the position k (0 initially), which with
   every pair of nodes found will increase by 1 unit. We also need to store the minimum spanning tree value into
   a variable that will show the final value at the end of the algoritm. After we do all of that, we need to
   apply UNION on the two sets containing the nodes that we just used and move on to the next edge.
   -> Complexity: O(E * log V) where E is the number of edges in the graph and V is the number of vertices.
   ( E is at most V^2 for a strongly connected graph )


*/ 


#include <stdlib.h>
#include<stdio.h>

#include "Header.h"

Profiler profiler("DisjointSets");



int nrOPERATIONS;


typedef struct node
{
	node* parent;
	int rank;
	int key;
};



typedef struct edge 
{
	int node1;
	int node2;
	int weight;
};




void MAKE_SET(node* x, int key)
{
	x->parent = x;

	x->rank = 0;

	x->key = key;

	nrOPERATIONS += 3;
}


void UNIONElements(node* x, node* y)
{
	nrOPERATIONS++;
	if (x->rank > y->rank)
	{
		nrOPERATIONS++;

		y->parent = x;
	}
	else
	{
		nrOPERATIONS++;

		x->parent = y;

		nrOPERATIONS++;
		if (x->rank == y->rank)
		{
			nrOPERATIONS++;
			y->rank = y->rank + 1;
		}
	}

}


node* FIND_SET(node* x)
{
	nrOPERATIONS++;
	if (x != x->parent)
		x->parent = FIND_SET(x->parent);

		return x->parent;
}



void UNIONSets(node* x, node* y)
{
	UNIONElements(FIND_SET(x), FIND_SET(y));
}






void Demo(int n)
{
	node* arrayOfSets = (node*)malloc(10 * sizeof(node));


	printf("----------CREATING THE SETS-------------\n\n");

	for (int i = 0; i < n; i++)
	{
		MAKE_SET(&arrayOfSets[i], i + 1);
		printf("The set %d holds the key %d \n\n", i + 1, arrayOfSets[i].key);
	}


	printf("\n\n\n");


	printf("----------UNION & FIND-------------\n\n");

	for (int j = 0; j < n / 2; j++)
		UNIONSets(&arrayOfSets[j], &arrayOfSets[j + 3]);

	for (int i = 0; i < n; i++)
	{
		printf("Node %d is in set %d \n", arrayOfSets[i].key, FIND_SET(&arrayOfSets[i])->key);
		printf("\n\n\n");
	}
}




void sortEdges(int n, edge* arrayOfEdges)
{
	int min;


	for (int i = 0; i < n - 1; i++)
	{
		min = i;

		for (int j = i + 1; j < n; j++)
			if (arrayOfEdges[j].weight < arrayOfEdges[min].weight)
				min = j;


		edge temp = arrayOfEdges[i];
		arrayOfEdges[i] = arrayOfEdges[min];
		arrayOfEdges[min] = temp;
	}
}



void KrusKalDemo(int n)
{
	printf("------------KRUSKAL DEMO-------------\n\n\n\n");


	srand(time(NULL));

	int i;

	edge* arrayOfEdges = (edge*)malloc(n * 4 * sizeof(edge));

	for (i = 0; i < n - 1; i++)
	{
		arrayOfEdges[i].node1 = i;
		arrayOfEdges[i].node2 = i+1;
		arrayOfEdges[i].weight = rand() % 30 + 1;
	}


	int restOfNodes1[46];
	int restOfNodes2[46];
	int restOfWeights[46];

	int nrOfEdgesLeft = 4 * n - (n - 1) + 1;

	FillRandomArray(restOfNodes1, nrOfEdgesLeft, 0, n-1);
	FillRandomArray(restOfNodes2, nrOfEdgesLeft, 0, n-1);

	FillRandomArray(restOfWeights, nrOfEdgesLeft, 1, 30);


	for (i = n - 1; i < 4 * n; i++)
	{
		if (restOfNodes1[i - (n - 1)] != restOfNodes2[i - (n - 1)])
		{
			arrayOfEdges[i].node1 = restOfNodes1[i - (n - 1)];
			arrayOfEdges[i].node2 = restOfNodes2[i - (n - 1)];
			arrayOfEdges[i].weight = restOfWeights[i - (n - 1)];
		}
		else
		{
			arrayOfEdges[i].node1 = restOfNodes1[i - (n - 1) + 1];
			arrayOfEdges[i].node2 = restOfNodes2[i - (n - 1)];
			arrayOfEdges[i].weight = restOfWeights[i - (n - 1)];

		}
	}

	printf("---ALL THE EDGES IN THE GRAPH---\n\n");

	for (int i = 0; i < 4 * n; i++)
	{
		printf("The edge is between the nodes %d and %d\n", arrayOfEdges[i].node1, arrayOfEdges[i].node2);
		printf("The weight of the edge is %d\n\n", arrayOfEdges[i].weight);
	}

	printf("\n\n\n");

	sortEdges(4 * n, arrayOfEdges);


	node* arrayOfSets = (node*)malloc(n * sizeof(node));

	int cost = 0;

	for (int i = 0; i < n; i++)
		MAKE_SET(&arrayOfSets[i], i);


	printf("----ALL THE EDGES (SORTED)----\n\n");

	for (int i = 0; i < 4 * n; i++)
	printf("%d (%d-%d)\n", arrayOfEdges[i].weight, arrayOfEdges[i].node1, arrayOfEdges[i].node2);

	printf("\n\n\n");

	int k = 0;

	edge* final = (edge*)malloc(n * sizeof(edge));


	for (int i = 0; i < 4 * n; i++)

		if (FIND_SET(&arrayOfSets[arrayOfEdges[i].node1]) != FIND_SET(&arrayOfSets[arrayOfEdges[i].node2]))
		{
			final[k] = arrayOfEdges[i];

			k++;

			cost += arrayOfEdges[i].weight;

			UNIONSets(&arrayOfSets[arrayOfEdges[i].node1], &arrayOfSets[arrayOfEdges[i].node2]);

		}

	printf("---SHOW MINIMUM SPANNING TREE---\n\n");

	for (int i = 0; i < k; i++)
		printf("The nodes %d and %d with the weight %d\n", final[i].node1, final[i].node2, final[i].weight);

	printf("\n\n -> the final cost is %d\n\n\n\n", cost);

}





void graphs()
{
	for (int n = 100; n <= 10000; n += 100)
	{
		srand(time(NULL));

		nrOPERATIONS = 0;

		edge* arrayOfEdges = (edge*)malloc(4 * n * sizeof(edge));


		for (int i = 0; i < n - 1; i++)
		{
			arrayOfEdges[i].node1 = i;
			arrayOfEdges[i].node2 = i + 1;
			arrayOfEdges[i].weight = rand() % 30 + 1;
		}


		int restOfNodes1[60000];
		int restOfNodes2[60000];
		int restOfWeights[60000];

		int nrOfEdgesLeft = 4 * n - (n - 1) + 1;

		FillRandomArray(restOfNodes1, nrOfEdgesLeft, 0, n-1);
		FillRandomArray(restOfNodes2, nrOfEdgesLeft, 0, n-1);

		FillRandomArray(restOfWeights, nrOfEdgesLeft, 1, 30);

		for (int i = n - 1; i < 4 * n; i++)
		{
			if (restOfNodes1[i - (n - 1)] != restOfNodes2[i - (n - 1)])
			{
				arrayOfEdges[i].node1 = restOfNodes1[i - (n - 1)];
				arrayOfEdges[i].node2 = restOfNodes2[i - (n - 1)];
				arrayOfEdges[i].weight = restOfWeights[i - (n - 1)];
			}
			else
			{
				arrayOfEdges[i].node1 = restOfNodes1[i - (n - 1) + 1];
				arrayOfEdges[i].node2 = restOfNodes2[i - (n - 1)];
				arrayOfEdges[i].weight = restOfWeights[i - (n - 1)];

			}
		}




		node* arrayOfSets = (node*)malloc(n * sizeof(node));

		int cost = 0;

		for (int i = 0; i < n; i++)
			MAKE_SET(&arrayOfSets[i], i);


		sortEdges(4 * n, arrayOfEdges);


		int k = 0;

		edge* final = (edge*)malloc(n * sizeof(edge));


		for (int i = 0; i < 4 * n; i++)


			if (FIND_SET(&arrayOfSets[arrayOfEdges[i].node1]) != FIND_SET(&arrayOfSets[arrayOfEdges[i].node2]))
			{
				final[k] = arrayOfEdges[i];

				k++;

				cost += arrayOfEdges[i].weight;

				UNIONSets(&arrayOfSets[arrayOfEdges[i].node1], &arrayOfSets[arrayOfEdges[i].node2]);

			}

		profiler.countOperation("OPERATIONS", nrOPERATIONS, n);

	}
	profiler.showReport();
}



int main()
{

	int n = 10;

    Demo(n);

	int n1 = 9;

	KrusKalDemo(n1);


	//graphs();

	return 0;
}