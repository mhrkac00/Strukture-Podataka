#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (60)

struct _tree;
typedef struct _tree* TPosition;
typedef struct _tree
{
	char city[MAX];
	int population;
	TPosition Left;
	TPosition Right;

}tree;

struct _list;
typedef struct _list* LPosition;
typedef struct _list
{
	char country[MAX];

	TPosition TreeRoot;
	LPosition next;

}list;


int ReadCountryFromFile(LPosition Head, char* FileName);
int InsertSortedIntoList(LPosition Head, char* CountryName);
TPosition CreateTreeElement(TPosition root, char* CityName, int pop);
int PrintList(LPosition Head);
int PrintInOrder(TPosition root);
int Print(TPosition root, int num);
LPosition CreateListElement(LPosition position);
LPosition FindCountry(LPosition Head, char* drzava);
TPosition ReadCityFromFile(TPosition root, char* drzava_dat);


int main()
{
	LPosition Head = NULL, NewEl = NULL;
	char FileName[MAX] = "datoteka.txt", CountryName[MAX] = { 0 };
	int num = 0;

	Head = CreateListElement(Head);
	NewEl = CreateListElement(NewEl);

	ReadCountryFromFile(Head, FileName);
	printf("Countries:\n");
	PrintList(Head->next);


		
	printf("Choose a country: ");
	scanf(" %s", CountryName);
	strcat(CountryName, ".txt");
	NewEl = FindCountry(Head, CountryName);
	if (!NewEl)
	{
		printf("There is not such a country in file!\n");
		return -1;
	}
	printf("\nEnter number of population: ");
	scanf("%d", &num);
	Print(NewEl->TreeRoot, num);
		
	
	return EXIT_SUCCESS;
}

LPosition CreateListElement(LPosition position)
{
	LPosition NewEl = NULL;
	NewEl = (LPosition)malloc(sizeof(list));

	if (!NewEl)
	{
		perror("Can't allocate memory!");
		return -1;
	}
	strcpy(NewEl->country, "");
	NewEl->next = NULL;
	NewEl->TreeRoot = NULL;
}

int ReadCountryFromFile(LPosition Head, char* FileName)
{
	FILE* fp = NULL;
	char cnt[MAX] = { 0 };

	fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Error opening fike!");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s\n", cnt);
		InsertSortedIntoList(Head, cnt);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}
int InsertSortedIntoList(LPosition Head, char* CountryName)
{
	LPosition NewEl = NULL;
	char pom[MAX] = { 0 };
	LPosition temp = NULL;
	temp = Head;

	NewEl = (LPosition)malloc(sizeof(list));
	if (NewEl == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return -2;
	}


	strcpy(NewEl->country, CountryName);
	NewEl->TreeRoot = NULL;
	NewEl->TreeRoot = ReadCityFromFile(NewEl->TreeRoot, CountryName);
	strcpy(pom, CountryName);

	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			temp->next = NewEl;
			NewEl->next = NULL;
			break;
		}
		else if (strcmp(pom, temp->next->country) < 0)
		{
			NewEl->next = temp->next;
			temp->next = NewEl;
			break;
		}
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
TPosition ReadCityFromFile(TPosition root, char* FileName)
{
	FILE* fp = NULL;
	char cty[MAX] = { "\0" };
	int pop = 0;

	fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Error opening file!");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d\n", cty, &pop);
		root = CreateTreeElement(root, cty, pop);
	}
	fclose(fp);
	return root;
}
TPosition CreateTreeElement(TPosition root, char* CityName, int pop)
{
	TPosition current = NULL;
	current = root;
	if (current == NULL)
	{
		current = (TPosition)malloc(sizeof(tree));
		if (current == NULL)
		{
			perror("Can't allocate memory!");
			return NULL;
		}
		strcpy(current->city, CityName);
		current->population = pop;
		current->Left = NULL;
		current->Right = NULL;
	}
	else if (pop == current->population)
	{
		if (strcmp(CityName, current->city) < 0)
			current->Left = CreateTreeElement(current->Left, CityName, pop);
		else if (strcmp(CityName, current->city) > 0)
			current->Right = CreateTreeElement(current->Right, CityName, pop);
	}
	else
	{
		if (pop < current->population)
			current->Left = CreateTreeElement(current->Left, CityName, pop);
		else if (pop > current->population)
			current->Right = CreateTreeElement(current->Right, CityName, pop);
	}
	return current;
}
int PrintList(LPosition Head)
{
	LPosition temp = NULL;
	temp = Head;
	while (temp != NULL)
	{
		printf("\n%s:\n", temp->country);
		PrintInOrder(temp->TreeRoot);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
int PrintInOrder(TPosition root)
{
	TPosition current = NULL;
	current = root;
	if (current== NULL)
		return -1;

	PrintInOrder(current->Left);
	printf("%s -> %d\n", current->city, current->population);
	PrintInOrder(current->Right);

	return EXIT_SUCCESS;
}
LPosition FindCountry(LPosition Head, char* CountryName)
{
	LPosition temp = NULL;
	temp = Head;
	while (temp->next != NULL && strcmp(CountryName, temp->country) != 0)
		temp = temp->next;

	return temp;
}
int Print(TPosition root, int num)
{
	TPosition current = NULL;
	current = root;
	if (current == NULL)
		return 0;

	Print(current->Left, num);

	if (num < current->population)
		printf("%s %d\n", current->city, current->population);

	Print(current->Right, num);

	return EXIT_SUCCESS;
}