/*
   @author Daniela Teodora Samuil
   @group 30421

	You are required to implement correctly and efficiently the management operations of an order
    statistics tree.You have to use a balanced, augmented Binary Search Tree. Each node in the tree holds, besides
    the necessary information, also the size field.

	

	We will first implement a function that builds the  balanced BST based on an ordered random array that we generate.
	How we will do that: We take the middle of the array and make it the root of the tree, then we recursevly call the
	same function on the left subtree (for the array starting at 0 and ending at middle-1) and on the right subtree
	(for the array starting at middle+1 and ending at n, where n is the total number of elements in the array). This will
	insure the balance of the tree. -> We can get the middle element in O(1) and we call the function for every split (because we have n
	elements => O(n) overall tree creation time)


	For Selecting an element from the tree, we store in a variable the size (nr of nodes) of the leftside of the tree,
	including the root. We compare this size with the given index and if they are equal, that means we found the element
	we are looking for. If not, if the value is smaller than the variable, we will recursevly call the function on the left
	subtree. If the value is greater, we will call the function on the right subtree, only this time we will modify the index
	for calling it, making it index-lenght (minus), because we need only the size on the rightside.
	- the function finds the ith smallest element in the array (we give the index that we want to find; ex: if we want to find the second
	smallest we will give i=2) => Complexity: O(h) where h is height of tree


	For Deletion we use an algorithm similar to the deletion of a node in a regular BST, only adapting it to change the size,
	as it is an augmented tree. We will have 3 cases: 1) the node is a leaf, case in which we simply delete it ; 2) the node
	has only one successor, either left or right, case in which we replace the node with its successor ; 3) the node has both
	children, case in which we will find its successor (minimum in the right subtree) and we will replace it with the value
	held in that node (that node being a leaf, because it is the leftmost on the right side, it is going to fall into the 
	first category and it's going to be really easy to delete). The deletion in BST: WORST: O(h) where h is height of tree.  
	In worst case, we may have to travel from root to the deepest leaf node. The height of a skewed tree may become n and the 
	time complexity of delete operation may become O(n).

	*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Header.h"


Profiler profiler("BST");


#define BUILD_TREE "BUILD TREE"
#define OS_SELECT "SELECT"
#define OS_DELETE "DELETE"


int nr_OP_Delete, nr_OP_Select, nr_OP_CreateTree;


typedef struct node {
	node* parent;
	node* right;
	node* left;
	int key;
	int size;
}Node;



Node* newNode(int k)
{
    node* n = (node*)malloc(sizeof(node));
	n->key = k;
	n->size = 0;
	n->parent = NULL;
	n->left = NULL;
	n->right = NULL;

	nr_OP_CreateTree += 5;

	return n;
}


int sized(Node* node)
{
	nr_OP_CreateTree++;
	if (node == NULL)
		return 0;
	else
		return(sized(node->left) + 1 + sized(node->right));

}


Node* CreateBST(int array[], int start, int end)
{
	if (start > end)
		return NULL;

	int mid = (start + end) / 2;
	node* root = newNode(array[mid]);

	root->left = CreateBST(array, start, mid - 1);
	root->right = CreateBST(array, mid + 1, end);

	if(root->left)
	root->left->parent = root;
	
	if(root->right)
	root->right->parent = root;

	root->size = sized(root);

	return root;
}



void padding(char ch, int n) 
{
	for (int i = 0; i < n; i++)
		putchar(ch);
}

void structure(Node* root, int level) 
{

	if (root == NULL) 
	{
		padding('\t\t', level);
		puts("-");
	}
	else 
	{
		structure(root->right, level + 1);
		padding('\t\t', level);
		printf("%d,%d\n", root->key, root->size);
		structure(root->left, level + 1);
	}
}

void prettyPrint(Node* tree)
{
	structure(tree, 0);
}



void demoCreateBST()
{
	int n = 11;

	int* Array = (int*)malloc(n*sizeof(int));

	FillRandomArray(Array, n, 0, 50, false, 1);

	Node* node = CreateBST(Array, 0, n - 1);

	prettyPrint(node);

}





Node* OS_select(Node* n, int i)
{
	nr_OP_Delete++;
	nr_OP_Select++;
	if (n)
	{

		int r;
		
		nr_OP_Delete++;
		nr_OP_Select++;
		if (n->left)
			r = n->left->size + 1;
		else
			r = 1;

		nr_OP_Delete++;
		nr_OP_Select++;
		if (i == r)
			return n;
		else
		{
			nr_OP_Delete++;
			nr_OP_Select++;
			if (i < r)
				return OS_select(n->left, i);
			else
				return OS_select(n->right, i - r);
		}
	}

	return NULL;
}



void demoSearch()
{
	int n = 11;

	int* Array = (int*)malloc(n * sizeof(int));

	FillRandomArray(Array, n, 0, 50, true, 1);

	Node* node = CreateBST(Array, 0, n - 1);

	srand(time(NULL));

	prettyPrint(node);

	for (int i = 0; i < 3; i++)
	{
		int find = 1 + rand()%11;
		printf("Index to be found: %d\n", find);

		Node* r;

		r = OS_select(node, find);

		if (r)
			printf("(key) %d and (size) %d\n\n", r->key, r->size);
		else
			printf("Not found\n\n");

	}
}




Node* findMinimum(Node* n)
{
	nr_OP_Delete++;
	if (n->left == NULL)
		return n;

	return findMinimum(n->left);
}



Node* OS_delete1(Node* n, int value)
{
	nr_OP_Delete++;
	if (n == NULL)
		return NULL;
	else
	{
		nr_OP_Delete += 2;
		if (n->left == NULL && n->right == NULL) // no child
		{
			Node* a = n->parent;

			if (a->left == n)
				a->left = NULL;
			else
				a->right = NULL;

			n = NULL;

			while (a != NULL)
			{
				a->size--;
				a = a->parent;
			}
		}
		else
		{
			nr_OP_Delete++;
			if (n->left == NULL) // only right child
			{
				Node* a = n->parent;

				a->right = n->right;

				while (a != NULL)
				{
					a->size--;
					a = a->parent;
				}
			}
			else
			{
				nr_OP_Delete++;
				if (n->right == NULL) // only left child
				{

					Node* a = n->parent;

					a->left = n->left;

					while (a != NULL)
					{
						a->size--;
						a = a->parent;
					}
				}
				else // two children
				{
					node* aux = findMinimum(n->right);

					nr_OP_Delete++;
					n->key = aux->key;

					OS_delete1(aux, aux->key);

				}

			}
		}
	}
}



void OS_delete(Node* n, int index)
{
	Node* aux = OS_select(n, index);
	OS_delete1(aux, aux->key); 

}



void demoDelete()
{
	int n = 11;

	int* Array = (int*)malloc(n * sizeof(int));

	FillRandomArray(Array, n, 0, 50, true, 1);

	Node* node = CreateBST(Array, 0, n - 1);

	srand(time(NULL));

	prettyPrint(node);

	int nr = 11;

	for (int i = 0; i < 3; i++)
	{
		int find = 1 + rand() % nr;
		printf("Index to be found: %d\n", find);

		Node* p;

		p = OS_select(node, find);

		if (p)
		{ 
			printf("(key) %d and (size) %d\n\n", p->key, p->size);

			OS_delete1(p, p->key);

			prettyPrint(node);
			printf("\n\n");

			nr--;
		}
	}
}




void graphics()
{
	for (int n = 100; n < 1000; n += 100)
	{
		nr_OP_CreateTree = 0;

		for (int index = 0; index < 5; index++)
		{
			int* Array = (int*)malloc(n * sizeof(int));

			FillRandomArray(Array, n, 0, 20000, true, 1);

			Node* root = CreateBST(Array, 0, n - 1);
		}

		profiler.countOperation(BUILD_TREE, n, nr_OP_CreateTree / 5);

		nr_OP_Delete = 0;

		for (int index = 0; index < 5; index++)
		{
			int* Array = (int*)malloc(n * sizeof(int));

			FillRandomArray(Array, n, 0, 20000, true, 1);

			Node* node = CreateBST(Array, 0, n - 1);

			srand(time(NULL));

			int nr = n;

			for (int i = 0; i < n; i++)
			{
				int find = 1 + rand() % nr;
				
				Node* p = OS_select(node, find);

				if (p)
				{
					OS_delete1(p, p->key);

					nr--;
				}
			}
		}

		profiler.countOperation(OS_DELETE, n, nr_OP_Delete / 5);

		nr_OP_Select = 0;

		for (int index = 0; index < 5; index++)
		{
			int* Array = (int*)malloc(n * sizeof(int));

			FillRandomArray(Array, n, 0, 20000, true, 1);

			Node* node = CreateBST(Array, 0, n - 1);

			srand(time(NULL));

			int nr = n;

			for (int i = 0; i < n; i++)
			{
				int find = 1 + rand() % nr;

				Node* p = OS_select(node, find);

				if(p)
					nr--;

			}
		}

		profiler.countOperation(OS_SELECT, n, nr_OP_Select / 5);

	}
}



int main()
{
	printf("------------TREE DEMO-------------\n");
	demoCreateBST();

	printf("\n\n\n");

	printf("--------------------SELECT DEMO-----------------------\n");
	demoSearch();

	printf("\n\n\n");

	printf("--------------------DELETE DEMO-----------------------\n");
	demoDelete();

	printf("\n\n\n");


	graphics();

	profiler.showReport();

	return 0;
}