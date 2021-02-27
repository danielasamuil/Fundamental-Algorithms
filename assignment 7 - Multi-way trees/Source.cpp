/*
   @author Daniela Teodora Samuil
   @group 30421


   You are required to implement correctly and efficiently linear time transformations between
   three different representations for a multi-way tree:

   
   For the first transformation (from an array to a multiway tree) we will use a structure that remembers the key of a node and an array of
   children for that particular node. We go through the array and compare each element with the root of the tree that we are going to construct
   (we have a function that return the root based on the parent vector). If the element in the array is equal with the root and it is also the
   Xs element (we verify that using a varianble OK, which is initially set to 1 and once it finds the Xs element equal with the root we turn it
   to 0) we will memorize the position where the particular element is found. We repeat this until we find all the children of the root, then we
   call the function recursevly for each child of the node. -> Each node would have an internal array for storing pointers to each of its
   m childeren: this implementation method has superior space complexity of O(m*n) where n is number of nodes and m is number of children for
   each node.


   For the second transformation(from a multiway tree to a binary tree) we will need a structure that remembers the key of a node, its child on
   the left side and the sibling on the right side. To do this transformation, we will use once again the number of children of each node.
   We take root of the multiway tree and based on the number of children that it has, we do the following thing: initialize a variable with 0 and
   create a while loop that gets the variable to the number equal with how many children root has. For the first node(i==0;the first child of the
   root) we create the child node of the root. From now on, for any i!=0 (any other child of the root), we will make it the sibling of the first 
   child. Then we recursevly call the same function on the node that was the first child, in such a way that we build our binary tree( child on 
   left & sibling on right ). The representation will have on the first coloumn the root of the tree, and on the following coloumns will be the
   children; each element in a coloumn will be sibling with each other element (divided by 2 different elements on the coloumn before).
   -> O(lgn) (?)

*/


#include <stdlib.h>
#include <stdio.h>

#include "Profiler.h"

Profiler profiler("MultiWayTrees");


typedef struct T1
{
	int key;
	T1* child;
	int nrOfChildren;
};



typedef struct T2 
{
	int key;
	T2* arrayOfChildren[11];
	int nrOfChildren;
};


typedef struct T3
{
	int key;
	T3* child;
	T3* sibling;
};



T2* returnRoot(int array[], int size, T2* node)
{
	for(int i=0; i<size; i++)
		if (array[i] == -1)
			node->key = i+1;

	node->nrOfChildren = 0;

	return node;
}



void InitializeArray(T1* parentVector, int size, int array[])
{
	for (int i = 0; i < size; i++)
	{
		parentVector[i+1].key = i;
		parentVector[i+1].nrOfChildren = 0;
	}
}



void calculateNumberOfChildrenT1(T1* parentVector, int array[], int size)
{

	for (int j = 0; j < size; j++)
		if (array[j] != -1)
			parentVector[array[j]].nrOfChildren++;

}



void setChildrenArray(T1* parentVector, int n, int array[])
{
	int* childrenCount = (int*)malloc(n * sizeof(int));


	for (int i = 0; i < n; i++)
		childrenCount[i+1] = 0;

	for (int j = 0; j < n; j++)
		if (array[j] != -1)
			childrenCount[array[j]]++;

	for (int i = 0; i < n; i++)
		parentVector[i].child = (T1*)malloc(childrenCount[i] * sizeof(T1));


	for (int i = 0; i < n; i++)
		if (array[i] != -1)
			parentVector[array[i]].child[parentVector[array[i]].nrOfChildren].key = i + 1;

	//for (int i = 0; i < n; i++)
		//printf("%d   ", parentVector[array[i]].child[parentVector[array[i]].nrOfChildren].key);

}



void calculateNumberOfChildrenT2(T2* parentVector, int array[], int size)
{

	for (int j = 0; j < size; j++)
		if (array[j] == parentVector->key)
			parentVector->nrOfChildren++;

}


void fromArrayToMultiway(T1* array, T2* root)
{
	
	int root1 = root->key;

	for (int i = 0; i <= array[root1].nrOfChildren; i++)
	{
		root->arrayOfChildren[i] = (T2*)malloc(sizeof(T2));

		root->arrayOfChildren[i]->nrOfChildren = 0;

		root->arrayOfChildren[i]->key = array[root1].child[i].key;

		root->nrOfChildren++;

		fromArrayToMultiway(array, root->arrayOfChildren[i]);
	}



}




T3* fromMultiwayToBinary(int n,int array[],T2* root , T3* rootB)
{
	T3* node = NULL;

	int root1 = root->key;

	int sum[12];

	for (int i = 1; i <= n; i++)
	{
		sum[i] = 0;

		for (int j = 0; j < n; j++)
			if (array[j] == i)
				sum[i]++;
	}

	int i = 0;

	printf("\n\n The node: %d \n", root1);

	while (i <= sum[array[root1]])
	{

		if (i == 0)
		{
			
			if (root->arrayOfChildren[i]->key == -1)
				return NULL;

			rootB->child = (T3*)malloc(sizeof(T3));

			rootB->child->child = NULL;
			rootB->child->sibling = NULL;

			rootB->child->key = root->arrayOfChildren[i]->key;


			if (rootB->child != NULL)
				node = rootB->child;
			else return NULL;


		}
		else
		{

			if (root->arrayOfChildren[i]->key == -1)
				return NULL;

			rootB->sibling = (T3*)malloc(sizeof(T3));

			rootB->sibling->child = NULL;
			rootB->sibling->sibling = NULL;

			rootB->sibling->key = root->arrayOfChildren[i]->key;


			fromMultiwayToBinary(n, array, root->arrayOfChildren[i-1], node);

			if (rootB->sibling != NULL)
				node = rootB->sibling;
			else return NULL;

		}

		i++;
	}

}




void printR1(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf(" %d ", array[i]);
	}
}



void printR2(T2* root, int level)
{
	printf("%*s%d\n\n", 4 * level, "", root->key);


	for (int j = 0; j < root->nrOfChildren; j++)
	{
		printR2(root->arrayOfChildren[j],level+1);
	}

}





int main()
{
	int n = 9;

	int array[9] = { 2,7,5,2,7,7,-1,5,2 };

	printf("----   REPRESENTATION 1   (PARENT VECTOR) ----\n");
	printR1(array, n);
	printf("\n\n\n\n");


	T2* node = (T2*)malloc(sizeof(T2));

	T2* root = returnRoot(array, n, node);

	calculateNumberOfChildrenT2(root, array, n);

	T1* parentVector = (T1*)malloc(9 * sizeof(T1));

	InitializeArray(parentVector, n, array);
	calculateNumberOfChildrenT1(parentVector, array, n);

	fromArrayToMultiway(parentVector, root);

	printf("----REPRESENTATION 2  (MULTIWAY TREE)   ----\n");
	//printR2(root, 0);
	printf("\n\n\n\n");

	return 0;

}