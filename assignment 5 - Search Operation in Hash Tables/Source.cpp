
/*

	*Quadratic Probing uses prime numbers for finding the place for the element to be put in. The prime numbers are adviced because
	they offer a larger variety of "rests" %.

	*The **insertion** is done until an empty place is found ( id == -1 ) . It tries to place the element N times ( size of the table ) hoping it will find
	an emtpy place at each step. Number of elements to be inserted should be < than table size.

	*The **search** operation is done until we find the key OR until we find -1 ( no element ) because from that point on it is pointless to add the
	same function over and over again.

	*From the **table** we can see that the avgEffortFound increases proportionally to the filling factor. ( more items, less empty spaces, harder to find )
*/

#include <stdlib.h>
#include <stdio.h>

#include "Header.h";

Profiler profiler("HashingTable");


int nrOP;


typedef struct
{
	int id;
	char name[30];
}Entry;



void Initialize(Entry* T[],int n)
{
	for (int i = 0; i < n; i++)
	{
		T[i] = (Entry*)malloc(sizeof(Entry));
		T[i]->id = -1;
		strcpy_s(T[i]->name," ");
	}
}



int QuadricProbing(int i, int m, int k)
{
	return ((k + 1 * i + 3 * i * i) % m);
}



void PrintHashTable(Entry* T[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (T[i]->id != -1)
			printf("%d %s\n", T[i]->id, T[i]->name);
	}
	printf("\n");
}


int HashInsert(int T[], int k, int m)
{
	int i = 0;
	do
	{
		int j = QuadricProbing(i, m, k);
		if (T[j] == -1)
		{
			T[j] = k;
			return j;
		}
		else i++;
	} while (i == m);
		printf("Hash table overflow");
}



int HashSearch(int T[], int k, int m)
{
	int i = 0;
	int j;

	do
	{
		j = QuadricProbing(i, m, k);
		nrOP++;
		if (T[j] == k)
			return j;
		i++;
	} while (T[j] == -1 || i == m);
		return -1;
}



int demoInsert(Entry* T[], int k, int m, const char string[])
{
	int i = 0;
	do
	{
		int j = QuadricProbing(i, m, k);
		if (T[j]->id == -1)
		{
			T[j]->id = k;
			strcpy_s(T[j]->name, string);
			return j;
		}
		else i++;
	} while (i == m);
	printf("Hash table overflow");
}



int demoSearch(Entry* T[], int m,int k)
{
	int i = 0;
	int j;

	do
	{
		j = QuadricProbing(i, m, k);
		if (T[j]->id == k)
		{
			printf("'%s' is found is the hash table \n", T[j]->name);
			return j;
		}

		i++;
	} while (T[j]->id == -1 || i == m);
	printf("Not found in the hash table\n");
	return -1;
		

}



void CreateTable(int* T)
{
	int n = 10007;

	double fillingFactor[] = { 0.8, 0.85 , 0.9 , 0.95 , 0.99 };


	for (int i = 0; i < 5; i++)
	{
		double averageFound = 0;
		double maxFound = 0;
		double averageNotFound = 0;
		double maxNotFound = 0;

		for (int j = 0; j < 5; j++)
		{
			int elements = (int)fillingFactor[i] * n;

			int* Array = (int*)malloc(sizeof(int));

			FillRandomArray(Array, elements,0,1999,true);

			Initialize(T, n);

			for (int i = 0; i < elements; i++)
				HashInsert(T, Array[i], n);

			int position = 0;

			double averageFound1 = 0;
			double maxFound1 = 0;
			double averageNotFound1 = 0;
			double maxNotFound1 = 0;
			//sir de indecsi(fillrand)
			//
		
			for (int found = 0; found < 1500; found++)
			{
				nrOP = 0;

				int x = HashSearch(T, Array[position], n);

			    position += elements / 1500;

				averageFound1 += nrOP;

				if (nrOP > maxFound1) maxFound1 = nrOP;
			}

			int position2 = 20000;

			for (int notfound = 0; notfound < 1500; notfound++)
			{
				nrOP = 0;

				int x = HashSearch(T, position2, n);

				position2++;

				averageNotFound1 += nrOP;

				if (nrOP > maxNotFound1) maxNotFound1 = nrOP;
			}

			averageFound1 = averageFound1 / 1500.0;
			averageNotFound1 = averageNotFound1 / 1500.0;

			averageFound += averageFound1;
			averageNotFound += averageNotFound1;

			maxFound += maxFound1;
			maxNotFound += maxNotFound1;

		}

		printf("FF   AvgF   MaxF   AvgNF   MaxNF\n");

		printf("%f   %f   %f   %f   %f\n",fillingFactor[i], averageFound / 5, maxFound / 5, averageNotFound / 5, maxNotFound / 5);
		
	}
}



void demoCreateTable(Entry* T[])
{
	int n = 10007;

	double fillingFactor = 0.8;

		double averageFound = 0;
		double maxFound = 0;
		double averageNotFound = 0;
		double maxNotFound = 0;

		for (int j = 0; j < 5; j++)
		{
			int elements = (int)fillingFactor * n;

			int Array[9000];

			FillRandomArray(Array, elements,1,1999);

			Initialize(T, n);

			for (int i = 0; i < elements; i++)
				HashInsert(T, Array[i], n);

			int position = 0;

			double averageFound1 = 0;
			double maxFound1 = 0;
			double averageNotFound1 = 0;
			double maxNotFound1 = 0;

			for (int found = 0; found < 1500; found++)
			{
				nrOP = 0;

				int x = HashSearch(T, Array[position], n);

				position++;

				averageFound1 += nrOP;

				if (nrOP > maxFound1) maxFound1 = nrOP;
			}

			int position2 = 20000;

			for (int notfound = 0; notfound < 1500; notfound++)
			{
				nrOP = 0;

				int x = HashSearch(T, position2, n);

				position2++;

				averageNotFound1 += nrOP;

				if (nrOP > maxNotFound1) maxNotFound1 = nrOP;
			}

			averageFound1 = averageFound1 / 1500.0;
			averageNotFound1 = averageNotFound1 / 1500.0;

			averageFound += averageFound1;
			averageNotFound += averageNotFound1;

			maxFound += maxFound1;
			maxNotFound += maxNotFound1;
		}

		printf("FF   AvgF   MaxF   AvgNF   MaxNF\n");

		printf("%f   %f   %f   %f   %f\n", fillingFactor, averageFound, maxFound, averageNotFound, maxNotFound);

	
}


void demoHashing()
{
	int n = 7;

	Entry* t[7];

	Initialize(t, n);

	demoInsert(t, 1, n, "Alex");
	demoInsert(t, 14, n, "Ion");
	demoInsert(t, 20, n, "Alexandra");
	demoInsert(t, 11, n, "Calin");
	demoInsert(t, 3, n, "Miruna");

	PrintHashTable(t, n);


	demoSearch(t, n, 33);

	demoSearch(t, n, 11);

	printf("\n\n");
}


int main()
{

	demoHashing();

	Entry* t[10007];

	demoCreateTable(t);

	CreateTable(t);

	return 0;
}