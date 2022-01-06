#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (256)



struct _tree;
typedef struct _tree* TPosition;
typedef struct _tree
{
	char city[MAX];
	int population;
	TPosition Left;
	TPosition Right;
	

}Tree;

struct _list;
typedef struct _list* LPosition;
typedef struct _list
{
	char country[MAX];
	TPosition tree;
	LPosition next;

}list;

int ReadCountryFromFile(LPosition Head, TPosition root, char* FileName);
TPosition ReadCityFromFile(TPosition root, char* FileName);
LPosition InsertSortedInList(LPosition Head, char* CountryName);
LPosition CreateListElement(char* CountryName);
LPosition FindBefore(LPosition Head, LPosition element);
int InsertAfter(LPosition position, LPosition element);
int PrintList(LPosition head);
TPosition CreateTreeElement(char* CityName, int pop);
TPosition InsertInTree(TPosition root, char* CityName, int pop);
int PrintInOrder(TPosition root);
int SearchList(LPosition Head, TPosition root, char* choice);
int SearchTree(TPosition root, int pop);

int main()
{
	list List = { .country = '\0', .next = NULL, .tree = NULL };
	LPosition Head = NULL;
	Head = &List;
	TPosition root = NULL;;

	ReadCountryFromFile(Head, root, "datoteka.txt");

	char choice[MAX];
	int pop;
	printf("\nEnter a country!\n");
	scanf("%s", choice);

	strcat(choice, ".txt");

	SearchList(Head, root, choice);

	return EXIT_SUCCESS;
}


int ReadCountryFromFile(LPosition Head, TPosition root, char* FileName)
{
	char buffer[MAX];
	FILE* fp = NULL;
	fp = fopen(FileName, "r");
	if (!fp)
	{
		printf("File is not opened!\n");
		return -1;
	}

	LPosition temp = NULL;
	
	printf("Countries:");
	while (!feof(fp))
	{
		fscanf(fp, "%s", buffer);
	
		temp = InsertSortedInList(Head, buffer);
		root = ReadCityFromFile(root, buffer);
		temp->tree = root;
		root = NULL;

	}
	
	PrintList(Head);

	
	

	fclose(fp);

	return EXIT_SUCCESS;

}

TPosition ReadCityFromFile(TPosition root, char* FileName)
{
	char buffer[MAX];
	int pop;
	FILE* fp = NULL;
	fp = fopen(FileName, "r");
	if (!fp)
	{
		printf("File is not opened!\n");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %d", buffer, &pop);
		root = InsertInTree(root, buffer, pop);
		
	}

	fclose(fp);



	return root;

}


LPosition InsertSortedInList(LPosition Head, char* CountryName)
{
	LPosition temp = NULL;
	temp = Head->next;
	LPosition NewEl = NULL;
	NewEl = CreateListElement(CountryName);

	LPosition Before = NULL;
	if (!NewEl)
		return NULL;

	if (!temp)
	{
		InsertAfter(Head, NewEl);
		return Head->next;
	}
	else
	{
		while (temp && strcmp(CountryName, temp->country))
			temp = temp->next;

		Before = FindBefore(Head, temp);
		InsertAfter(Before, NewEl);
	}

	return Before->next;
}

LPosition CreateListElement(char* CountryName)
{
	LPosition NewEl = NULL;
	NewEl = (LPosition)malloc(sizeof(list));
	if (!NewEl)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(NewEl->country, CountryName);
	NewEl->next = NULL;
	NewEl->tree = NULL;

	return NewEl;

}

LPosition FindBefore(LPosition Head, LPosition element)
{
	LPosition temp = Head;

	while (temp->next != element)
		temp = temp->next;

	return temp;
}

int InsertAfter(LPosition position, LPosition element)
{
	element->next = position->next;
	position->next = element;
	
	return EXIT_SUCCESS;
}

int PrintList(LPosition head)
{
	LPosition temp = NULL;
	temp = head->next;

	while (temp->next)
	{
		printf("\n%s\n", temp->country);
		PrintInOrder(temp->tree);
		temp = temp->next;
	}

	


	return EXIT_SUCCESS;
}

TPosition CreateTreeElement(char* CityName, int pop)
{
	TPosition NewEl = NULL;
	NewEl = (TPosition)malloc(sizeof(Tree));
	if (!NewEl)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(NewEl->city, CityName);
	NewEl->population = pop;
	NewEl->Left = NULL;
	NewEl->Right = NULL;

	return NewEl;

}

TPosition InsertInTree(TPosition root, char* CityName, int pop)
{
	TPosition current = NULL;
	current = root;

	TPosition NewEl = NULL;
	

	if (current == NULL)
	{
		NewEl = CreateTreeElement(CityName, pop);
		return NewEl;
	}
	else if (pop < current->population)
		current->Left = InsertInTree(current->Left, CityName, pop);
	else if (pop > current->population)
		current->Right = InsertInTree(current->Right, CityName, pop);
	else
		free(NewEl);

	return current;
}

int PrintInOrder(TPosition root)
{
	TPosition current = root;
	current = root;

	if (current != NULL)
	{
		PrintInOrder(current->Left);
		printf("%d -> %s \n", current->population, current->city);
		PrintInOrder(current->Right);
	}
	

	return EXIT_SUCCESS;
}


int SearchList(LPosition Head, TPosition root, char* choice)
{
	LPosition temp = NULL;
	temp = Head->next;
	int pop;

	while (temp->next)
	{
		
		if (strcmp(temp->country, choice)==0)
		{
			printf("Enter a number of population: ");
			scanf("%d", &pop);
			SearchTree(temp->tree, pop);
			return EXIT_SUCCESS;
		}
		

		temp = temp->next;

	}

	printf("There is no such a country in this file!");

}

int SearchTree(TPosition root, int pop)
{
	TPosition current = NULL;
	current = root;
	int br = 0;

	if (current != NULL)
	{
		if (current->population > pop)
		{
			SearchTree(current->Left, pop);
			printf("%d -> %s \n", current->population, current->city);
			SearchTree(current->Right, pop);
		}
		else
		{
			SearchTree(current->Right, pop);

		}
	}



	return EXIT_SUCCESS;
		

}