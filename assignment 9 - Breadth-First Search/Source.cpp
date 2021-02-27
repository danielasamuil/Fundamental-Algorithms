/*
	@author: Samuil Daniela Teodora
	@group: 30421


	You are required to implement correctly and efficiently the Breadth-First Search (BFS)
 graph algorithm (Section 22.2 from the book1). For graph representation, you should use adjacency lists.
 You are also required to pretty-print the resulting tree/forest of trees (use Assignment 8 to
 achieve this) – only for the demo.


  First we need to create the graph, and for that we will use a vector from 0 to V(number of vertices) to
  name our nodes, we will give them all the color WHITE and the next pointer will be NULL (we need the next
  pointer since we are going to represent the graph using adjacency lists). Then we need to generate E edges 
  between 2 random selected nodes. To verify that we use a function that returns a boolean value, false if the
  nodes selected are identical, 1 if we can sucessfully add the node to the adjacency list of the other node.

  Then we need to implement the functions that are working with the queue, enqueue, which will add an element 
  as last in the queue, and dequeue, which will delete the first element in the queue. -> Complexity: O(1) for both 
  enqueue and dequeue => total time devoted to the queue is O(V)

  As for the BFS, we initialize a parrent array (only for the demo) with the values -2 for all elements and
  then, for the root, we place the value -1. We initialize the queue and then we give to the starting node, given
  as paramenter, the color GREY and add it to the queue. We then initialize a new variable with the value of the
  element returned from the function dequeue, and for all the nodes that can be reached from that particular node
  we set their color to GREY, insert it into the queue if their color is WHITE
  and set their parrent as the value of the node extracted from dequeue. When we don't
  have any node lest in the adjacency list of our current node, we can turn its color to BLACK.

   - the adjacency list Adj[u] consists of an array that contains all the vertices v such that there is an edge between u and v
   - for a node u that has an adjacency list, there is a directed edge starting at u and terminating at each of its nodes in the list
   - because the procedure scans each the adjacency list of each vertex only when the vertes is dequeued, it scans each list at most once.
   since the sum of the lenghts of all adjacency lists is (theta)(E), the total time spent in scanning the adjacency lists is O(E).

   => the overall running time is O(V+E), which is linear


*/




#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Header.h"


int operations;


Profiler profiler("BFS");



typedef struct nodeAdjList
{
	int key;
	nodeAdjList* next;
	char color;
};


struct nodeQueue
{
	int key;
	nodeQueue* next;
};


struct queue
{
	nodeQueue* first;
	nodeQueue* last;
};




void InitializationNodesForGraph(nodeAdjList* G[], int n, bool OK)
{
	if(OK)
	printf("The nodes in the graph:\n\n");

	for (int i = 0; i < n; i++)
	{
		nodeAdjList* graphNodes = (nodeAdjList*)malloc(sizeof(nodeAdjList));

		graphNodes->key = i;
		
		graphNodes->next = NULL;

		graphNodes->color = 'W';

		G[i] = graphNodes;

		if(OK)
		printf("%d   ", G[i]->key);
	}

	if (OK)
	printf("\n\n\n");
}



int insertNodeToAdjList(nodeAdjList* node, int key)
{

	if (node->key == key)  //they are the same node
		return 0;
	else
		if(node->next != NULL)
		  while (node->next != NULL && node->next->key != key)
		  {
			node = node->next;
		  }
	

		if (node->next == NULL)
		{
			nodeAdjList* newNode = (nodeAdjList*)malloc(sizeof(nodeAdjList));

			newNode->key = key;
			newNode->next = NULL;
		    newNode->color = 'W';

			node->next = newNode;

			return 1;
		}


	return 0;
}




nodeAdjList** createGraph(int V, int E, bool OK)
{
	srand(time(NULL));


	nodeAdjList** G = (nodeAdjList**)malloc(V * sizeof(nodeAdjList));

	InitializationNodesForGraph(G, V, OK);


	int aux = E;

	if(OK)
	printf("The edges in the graph:\n\n");

	while (aux)
	{
		int node1 = rand() % V;
		int node2 = rand() % V;

		if (insertNodeToAdjList(G[node2], node1) && insertNodeToAdjList(G[node1], node2))
		{
			aux--;

			if (OK)
			printf("%d - %d \n", node1, node2);
		}
	}

	if (OK)
	printf("\n\n\n");

	if (OK)
	printf("The adjacency lists: \n\n");

	if (OK)
	for (int i = 0; i < V; i++)
	{
		
		printf("for the node %d : ", G[i]->key);

		nodeAdjList* node = G[i]->next;

		while (node != NULL)
		{
			printf("%d ", node->key);

			node = node->next;
		}
		printf("\n");
	}

	return G;
}









void initializeQueue(queue* Q)
{
	Q->first = NULL;
	Q->last = NULL;
}




void enqueue(queue* Q, int key)
{
	nodeQueue* node = (nodeQueue*)malloc(sizeof(nodeQueue));

	node->key = key;
	node->next = NULL;


	if (Q->first == NULL)
	{
		Q->first = node;
		Q->last = node;
	}
	else
	{
		Q->last->next = node;
		Q->last = node;
	}
}



int dequeue(queue* Q)
{
	int x;
	

	if (Q->first != NULL)                     
	{
		
		x = Q->first->key;
		
		Q->first = Q->first->next;

		if (Q->first == NULL)
			Q->last = NULL;

		return x;
	}
	else
	 return -1;
}








struct T1
{
	int key;
	int nrOfChildren;
	T1* children;
};



struct T2
{
	int key;
	int nrOfChildren;
	T2* arrayOfChildren[9];
};



struct T3
{
	int key;
	T3* child;
	T3* sibling;
};




void printR1(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf(" %d ", array[i]);
	}
}




void Initialize1(int size, T1* parentVector, int array[])
{

	int* countingChildren = (int*)malloc((size - 1) * sizeof(int));

	for (int i = 0; i < size; i++)
	{
		parentVector[i].nrOfChildren = 0;
		parentVector[i].key = i;

		countingChildren[i] = 0;

		if (array[i] != -1)
			countingChildren[array[i]]++;
	}


	for (int j = 0; j < size; j++)
		parentVector[j].children = (T1*)malloc(countingChildren[j] * sizeof(T1));


	for (int k = 0; k < size; k++)
		if (array[k] != -1)
		{
			parentVector[array[k]].nrOfChildren++;
			parentVector[array[k]].children[parentVector[array[k]].nrOfChildren].key = k;
		}
}





void Initialize2(int rootValue, T2* multiwayRoot)
{
	multiwayRoot->key = rootValue;
	multiwayRoot->nrOfChildren = 0;
}




void fromParentVectorToMultiway(T1* parentVector, T2* multiwayRoot, int root)
{

	for (int i = 0; i < parentVector[root].nrOfChildren; i++)
	{
		multiwayRoot->arrayOfChildren[i] = (T2*)malloc(sizeof(T2));

		multiwayRoot->arrayOfChildren[i]->nrOfChildren = 0;

		multiwayRoot->arrayOfChildren[i]->key = parentVector[root].children[i+1].key;

		multiwayRoot->nrOfChildren++;

		fromParentVectorToMultiway(parentVector, multiwayRoot->arrayOfChildren[i], multiwayRoot->arrayOfChildren[i]->key);

	}
}




void Initialize3(T3* binaryRoot, int rootValue)
{

	binaryRoot->key = rootValue;
	binaryRoot->child = NULL;
	binaryRoot->sibling = NULL;
}



void fromMultiwayToBinary(T2* multiwayRoot, T3* binaryRoot)
{
	T3* newNode = NULL;

	for (int i = 0; i < multiwayRoot->nrOfChildren; i++)
		if (i == 0)
		{

			binaryRoot->child = (T3*)malloc(sizeof(T3));

			binaryRoot->child->key = multiwayRoot->arrayOfChildren[i]->key;
			binaryRoot->child->child = NULL;
			binaryRoot->child->sibling = NULL;

			newNode = binaryRoot->child;
		}
		else
		{
			newNode->sibling = (T3*)malloc(sizeof(T3));

			newNode->sibling->key = multiwayRoot->arrayOfChildren[i]->key;
			newNode->sibling->child = NULL;
			newNode->sibling->sibling = NULL;

			fromMultiwayToBinary(multiwayRoot->arrayOfChildren[i-1], newNode);

			newNode = newNode->sibling;

		}
}


void printR3(T3* binaryRoot, int level)
{
	printf("%*s%d\n", 4 * level, "", binaryRoot->key);

	if (binaryRoot->child != NULL)
	{
		printf("\n");
		printR3(binaryRoot->child, level + 1);
	}

	if (binaryRoot->sibling != NULL)
	{
		printf("\n");
		printR3(binaryRoot->sibling, level);
	}
}









void BFS(nodeAdjList* G[], nodeAdjList* s, int V, bool OK)
{
	int* parentArray = (int*)malloc(V * sizeof(int));
	int* OKArray= (int*)malloc(V * sizeof(int));

	if (OK)
	{
		for (int i = 0; i < V; i++)
			parentArray[i] = -2;


		parentArray[s->key] = -1;
	}

	for (int i = 0; i < V; i++)
		OKArray[i] = 0;


	queue* Q=(queue*)malloc(sizeof(queue));

	initializeQueue(Q);

	s->color = 'G';

	operations++;

	enqueue(Q, s->key);

	operations+=3;


	while (Q->first)
	{
	
		int u = dequeue(Q);

		operations+=2;

		nodeAdjList* x = G[u];


		while (x->next)
		{
			x = x->next;
			
			operations++;
			if ((OKArray[x->key] == 0) && (x->color=='W'))
			{
				if (OK)
					if (parentArray[x->key] != -1 && OKArray[x->key]==0)
						{
							parentArray[x->key] = u;

							//printf("%d   ", parentArray[x->key]);

							OKArray[x->key] = 1;
						}

				OKArray[x->key] = 1;

				x->color = 'G';

				operations++;

				
				enqueue(Q, x->key);
				operations+=3;

					
			
			}
		}

		x->color = 'B';
		operations++;

	}


	if (OK)
	{
		printf("\n\nParent Vector : ");
		printR1(parentArray, V);
		printf("\n\n");


		T1* parentArr = (T1*)malloc(V * sizeof(T1));
		
		Initialize1(V, parentArr, parentArray);



		T2* multiwayRoot = (T2*)malloc(sizeof(T2));

		Initialize2(s->key, multiwayRoot);

		fromParentVectorToMultiway(parentArr, multiwayRoot, s->key);




		T3* binaryRoot = (T3*)malloc(sizeof(T3));

		Initialize3(binaryRoot, s->key);

		fromMultiwayToBinary(multiwayRoot, binaryRoot);


		printf("\n\n\nPretty print : \n\n");
		
		printR3(binaryRoot, 0);
	}
}




void graphs()
{
	int V = 100;

	for (int E = 1000; E <= 4900; E += 100)
	{
		operations = 0;

		nodeAdjList** G = (nodeAdjList**)malloc(V * sizeof(nodeAdjList));

		nodeAdjList** graph = createGraph(V, E, 0);

		BFS(graph, graph[0], V, 0);

		//printf("%d ", E);

		profiler.countOperation("V SET", E, operations);

	}



	int e = 4900;

	for (int v = 100; v <= 200; v += 10)
	{
		operations = 0;

		nodeAdjList** G = (nodeAdjList**)malloc(v * sizeof(nodeAdjList));

		nodeAdjList** graph = createGraph(v, e, 0);

		BFS(graph, graph[0], v, 0);

		//printf("%d ", v);

		profiler.countOperation("E SET", v, operations);
	}

}




int main()
{
	int V = 6;

	int E = 10;


	printf("------CREATE GRAPH---------\n\n");
	
	nodeAdjList** graph = createGraph(V, E, 1);

	printf("\n\n\n\n");

	printf("-------BFS---------\n\n");

	BFS(graph, graph[0], V, 1);


	graphs();

	profiler.showReport();

	printf("gata");
	return 0;
}