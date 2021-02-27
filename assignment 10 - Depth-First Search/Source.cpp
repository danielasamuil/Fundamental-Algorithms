/*
	@author  Samuil Daniela Teodora
	@group   30421

 You are required to implement correctly and efficiently the depth­first search
 algorithm (DFS). For graph representation, you should use adjacency lists. You also have to:
­ - Implement the Tarjan algorithm for detecting strongly connected components
­ - Implement topological sorting 


 --DFS--
 We implement DFS using adjacency lists. Taking, in order, all the nodes of the graph, and we take a look into
 their neighbours. Unlike BFS, we don't go through all the nodes in ones adjacency list, rather we visit just one
 neighbour and then move on to its adjacency list and so on. To represent this kind of search i opted for a
 paranthesis representation ( we open the paranthesis the first time we find a node and we close it just when
 the node becomes black, that means when we finish visiting all its neighbours ). Also, DFS has some extra
 elements unlike BFS, and these are the timestamps: they remember the discovery and finishing time of a specific
 node. The running time of this algorithm is O(V+E), since the initialization of the nodes characteristics take
 O(V) and the sum of the execution time for adjacency lists is O(E).

 --TOPOLOGICAL SORT--
 It is an algorithm that uses DFS(mostly its finishing times) to insert each vertex into a list & it returns
 the list. It is built exactly like the DFS, with the exception that we add the list implementation and each
 time a node has all of its neighbours visited ( when we can assure its finishing time ) we are going to insert
 it in the list. The final result will be constructed in such a way that, if there is an edge between verteces
 (u & v), u will come before v in the list. Running time: O(V+E) since this is DFSs running time and inserting
 elements into such a structure takes only O(1).

 --TARJAN--
 It is an algorithm that helps us find the strongly connected components of a directed graph.Any vertex that is not
 on a directed cycle forms a strongly connected component all by itself. This method uses DFS for searching the 
 nodes and a stack to memorize the order in which the nodes are visited. A node remains on the stack after it
 has been visited iff there exists a path in the input graph from it to some node earlier on the stack. We add
 two new characteristics for a node: index(time when it was discovered) and lowlink ( the smallest index of any node
 known to be reachable from v through v's DFS subtree, including itself ). Therefore v must be left on the stack if
 v.lowlink < v.index, whereas v must be removed as the root of a strongly connected component if v.lowlink == v.index.
 ->Complexity: O(V+E) ; 

*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Header.h"

Profiler profiler("DFS");
int operations;

/************************** GRAPH ************************************************/

typedef struct nodeAdjList
{
	int key;
	nodeAdjList* next;
	char color;
	int discovered;
	int finished;

	int index;
	int lowlink;
};


void InitializationNodesForGraph(nodeAdjList* G[], int n, bool OK)
{
	if (OK)
		printf("The nodes in the graph:\n\n");

	for (int i = 0; i < n; i++)
	{
		nodeAdjList* graphNodes = (nodeAdjList*)malloc(sizeof(nodeAdjList));

		graphNodes->key = i;

		graphNodes->next = NULL;

		graphNodes->color = 'W';

		graphNodes->discovered = 0;

		graphNodes->finished = 0;

		graphNodes->index = 0;

		graphNodes->lowlink = 0;


		G[i] = graphNodes;

		if (OK)
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
		if (node->next != NULL)
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

	if (OK)
		printf("The edges in the graph:\n\n");

	while (aux)
	{
		int node1 = rand() % V;
		int node2 = rand() % V;

		if (insertNodeToAdjList(G[node2], node1))
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


/*********************** TREE *************************/

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
	T2* arrayOfChildren[20];
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

			fromMultiwayToBinary(multiwayRoot->arrayOfChildren[i - 1], newNode);

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

/************************ DFS ***********************/

int timeDFS;

void DFS_VISIT(nodeAdjList *G[], nodeAdjList * u, bool OK, int OKArray[], int parentArray[])
{
	timeDFS++;

	u->discovered = timeDFS;
	operations++;
	u->color = 'G';
	operations++;
	OKArray[u->key] = 1;

	nodeAdjList* node = u;
	if(OK)
	printf("(%d ", node->key);

	while (node->next != NULL)
	{
		node = node->next;

		operations++;
		if (OKArray[node->key] == 0 && node->color == 'W')
		{
			parentArray[node->key] = u->key;

			DFS_VISIT(G, G[node->key], OK, OKArray, parentArray);
			if(OK)
			printf(" %d)", node->key);
		}
	}

	u->color = 'B';
	operations++;

	timeDFS++;

	u->finished = timeDFS;
	operations++;

}


void DFS(nodeAdjList** G, int V,bool OK)
{

	int* parentArray = (int*)malloc(V * sizeof(int));
	int* OKArray = (int*)malloc(V * sizeof(int));

	for (int i = 0; i < V; i++)
		OKArray[i] = 0;

    timeDFS = 0;

	int x = 1;

	for (int i = 0; i < V; i++)
	{
		operations++;
		if (OKArray[i] == 0 && G[i]->color == 'W')
		{ 
			if(OK)
			printf("group %d of strongly connected components:\n\n", x);
			x++;

			if (OK)
			{
				for (int j = 0; j < V; j++)
					parentArray[j] = -2;

				parentArray[i] = -1;
			}

			DFS_VISIT(G, G[i],OK,OKArray,parentArray);
			if(OK)
			printf(" %d)", G[i]->key);

			if (OK)
				printf("\n\n\n");

			if (OK)
			{
				printf("Parent Vector : ");
				printR1(parentArray, V);
				printf("\n\n\n");

				/*T1* parentArr = (T1*)malloc(V * sizeof(T1));
				Initialize1(V, parentArr, parentArray);

				T2* multiwayRoot = (T2*)malloc(sizeof(T2));
				Initialize2(G[i]->key, multiwayRoot);
				fromParentVectorToMultiway(parentArr, multiwayRoot, G[i]->key);
				
				T3* binaryRoot = (T3*)malloc(sizeof(T3));
				Initialize3(binaryRoot, G[i]->key);
				fromMultiwayToBinary(multiwayRoot, binaryRoot);

				printf("\n\n\nPretty print : \n\n");
				printR3(binaryRoot, 0);*/

			}
		}
	}
}

void graphs()
{
	int V = 100;

	for (int E = 1000; E <= 5000; E += 100)
	{
		operations = 0;
		nodeAdjList** G = (nodeAdjList**)malloc(V * sizeof(nodeAdjList));
		nodeAdjList** graph = createGraph(V, E, 0);

		DFS(graph, V, 0);

		profiler.countOperation("V SET", E, operations);
	}

	int e = 9000;

	for (int v = 100; v <= 200; v += 10)
	{
		operations = 0;
		nodeAdjList** G = (nodeAdjList**)malloc(v * sizeof(nodeAdjList));
		nodeAdjList** graph = createGraph(v, e, 0);

		DFS(graph, v, 0);

		profiler.countOperation("E SET", v, operations);
	}
}

/******************* TOPOLOGICAL SORT *****************/

typedef struct nodeList
{
	int key;
	nodeList* next;
};


typedef struct list
{
	nodeList* first;
	nodeList* last;
};

void initializeList(list* list)
{
	list->first = NULL;
	list->last = NULL;
}

void insertFirst(list* list, int key)
{
	nodeList* node = (nodeList*)malloc(sizeof(nodeList));

	node->key = key;
	node->next = list->first;

	if (list->first == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
		list->first = node;
		
}

void printList(list* listt)
{
	nodeList* node = listt->first;

	if (listt->first == NULL) 
		printf("There is no node");
	else
		while (node != NULL)
		{
			printf("%d ", node->key);
			node = node->next;
		}

	printf("\n");
}

int timeDFStopological;

void DFS_VISIT_TOP(nodeAdjList* G[], nodeAdjList* u, bool OK, int OKArray[], list* listt)
{
	timeDFStopological++;

	u->discovered = timeDFStopological;
	u->color = 'G';

	OKArray[u->key] = 1;

	nodeAdjList* node = u;

	while (node->next != NULL)
	{
		node = node->next;

		if (OKArray[node->key] == 0 && node->color == 'W')
			DFS_VISIT_TOP(G, G[node->key], OK, OKArray,listt);
	}

	u->color = 'B';

	timeDFStopological++;

	u->finished = timeDFStopological;

	printf("Node %d is finished and we insert it into the list\n", u->key);

	insertFirst(listt, u->key);
}


void DFS_TOP(nodeAdjList** G, int V, bool OK, list* listt)
{
	int* OKArray = (int*)malloc(V * sizeof(int));

	for (int i = 0; i < V; i++)
		OKArray[i] = 0;

	timeDFStopological = 0;

	printf("\nthe topological sort:\n\n");

	for (int i = 0; i < V; i++)
	{
		if (OKArray[i] == 0 && G[i]->color == 'W')
		{
			DFS_VISIT_TOP(G, G[i], OK, OKArray,listt);
			printf("\n");
			printList(listt);
			printf("\n\n");
			initializeList(listt);
		}
	}
}

void topologicalSort(int V, int E, bool OK)
{
	nodeAdjList** graph = createGraph(V, E, OK);

	list* listt = (list*)malloc(sizeof(list));
	initializeList(listt);

	DFS_TOP(graph, V, OK, listt);
}

/******************* TARJAN ********************/

struct stack
{
	int maxsize;
	int top;
	int items[10];
};

void initializeStack(stack* stackk,int capacity)
{
	stackk->maxsize = capacity;
	stackk->top = -1;

	for (int i = 0; i < capacity; i++)
		stackk->items[i] = -1;
}

int isEmpty(stack* s)
{
	if (s->top == -1)
		return 1;
	else return 0;
}

int isFull(stack* s)
{
	if (s->top == s->maxsize - 1)
		return 1;
	else return 0;
}

int push(stack* s, int x)
{
	if (isFull(s))
		return -1;
	else
	{
		s->top++;
		s->items[s->top] = x;
		return 1;
	}
}

int pop(stack* s)
{
	if (isEmpty(s))
		return -1;
	else
		return s->items[s->top];
		
}

void strongconnect(nodeAdjList** G, nodeAdjList* source, int identified[], int index, stack* stackk, int onStack[], int V)
{
	source->index = index;
	source->lowlink = index;
	index++;
	identified[source->key] = 1;

	push(stackk, source->key);
	printf("element added on stack: %d\n", source->key);
	onStack[source->key] = 1;

	nodeAdjList* node = source;

	while (node->next != NULL)
	{
		node = node->next;
		if (identified[node->key] == 0)
		{
			strongconnect(G, G[node->key], identified, index, stackk, onStack,V);
			if (source->lowlink > G[node->key]->lowlink)
				source->lowlink = G[node->key]->lowlink;
		}
		else
			if(onStack[node->key]==1)
				if (source->lowlink > G[node->key]->index)
					source->lowlink = G[node->key]->index;
	}

	if (source->lowlink == source->index)
	{
		int* SCC = (int*)malloc(V* sizeof(int));
		int capacity = 0;

		int w;
		do
		{
			w = pop(stackk);
			stackk->top--;
			printf("element popped: %d\n", w);
			onStack[w] = 0;
			SCC[capacity] = w;
			capacity++;

		} while (w != source->key);

		printf("\n\nThe SCC:\n");
		for (int i = 0; i < capacity; i++)
			printf("%d  ", SCC[i]);
		printf("\n\n");
	}
}

void tarjan(int V, int E)
{
	nodeAdjList** graph = createGraph(V, E, 1);
	printf("\n\n");

	int index = 0;

	int* identified = (int*)malloc(V * sizeof(int));
	stack* stackk = (stack*)malloc(V * sizeof(stack));
	int* onStack = (int*)malloc(V * sizeof(int));

	initializeStack(stackk, V);

	for (int i = 0; i < V; i++)
	{
		identified[i] = 0;
		onStack[i] = 0;
	}

	for (int i = 0; i < V; i++)
		if (identified[i] == 0)
			strongconnect(graph,graph[i],identified, index, stackk, onStack,V);
}


/********************* MAIN **************************/

int main()
{
	int V = 6;
	int E = 10;
	
	printf("------ CREATE GRAPH ---------\n\n");
	nodeAdjList** graph = createGraph(V, E, 1);
	printf("\n\n\n\n");
	
	printf("------ DFS -------\n\n");
	DFS(graph, V, 1);
	graphs();
	profiler.showReport();

	printf("------------- TOPOLOGICAL SORT ----------------\n\n");
	topologicalSort(V, E, 1);

	printf("----------- TARJAN ---------------\n\n");
	tarjan(V, E);


	return 0;
}