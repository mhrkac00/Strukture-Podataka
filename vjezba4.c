#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXL 1024

struct _Polinom;
typedef struct _Polinom* position;
typedef struct _Polinom
{
	int koeficjent;
	int eksponent;
	position next;

}Polinom;

int ProcitajIzDat(position Head1, position Head2, char* nazivDat);
int Procitaj(position Head, char* string, int n);
int umetniSortirano(position Head, int k, int e);
position CreateElement(int k, int e);
int IspisiPolinom(position first);
int ZbrojiPolinome(position First1, position First2, position HeadSuma);
int OcistiNule(position Head);
int PomnoziPolinome(position First1, position First2, position HeadProdukt);

int main(int argc, char** argv)
{

	position Head1 = NULL, Head2 = NULL, HeadSuma = NULL, HeadProdukt = NULL;

	Head1 = (position)malloc(sizeof(Polinom));
	Head2 = (position)malloc(sizeof(Polinom));
	HeadSuma = (position)malloc(sizeof(Polinom));
	HeadProdukt = (position)malloc(sizeof(Polinom));

	if (!Head1 || !Head2 || !HeadSuma || !HeadProdukt)
	{
		printf("Greska!\n");
		return -1;

	}

	Head1->next = NULL;
	Head2->next = NULL;
	HeadSuma->next = NULL;
	HeadProdukt->next = NULL;
	ProcitajIzDat(Head1, Head2, "polinomi.txt");

	printf("Prvi polinom:\t");
	IspisiPolinom(Head1->next);

	printf("\n\nDrugi polinom:\t");
	IspisiPolinom(Head2->next);

	ZbrojiPolinome(Head1->next, Head2->next, HeadSuma);
	printf("\n\nZbroj polinoma:\t");
	IspisiPolinom(HeadSuma->next);

	PomnoziPolinome(Head1->next, Head2->next, HeadProdukt);
	printf("\n\nProdukt polinoma:   ");
	IspisiPolinom(HeadProdukt->next);

	printf("\n");

	return EXIT_SUCCESS;
}

int ProcitajIzDat(position Head1, position Head2, char* nazivDat)
{
	FILE* fp = NULL;
	fp = fopen(nazivDat, "r");
	if (!fp)
	{
		printf("Neuspijesno otvaranje datoteke!\n");
		return -1;
	}
	char string[MAXL];

	fgets(string, MAXL, fp);
	Procitaj(Head1, string, strlen(string));
	fgets(string, MAXL, fp);
	Procitaj(Head2, string, strlen(string));

	fclose(fp);


	return EXIT_SUCCESS;
}

int Procitaj(position Head, char* string, int n)
{
	string[n] = 0;
	int k = 0, e = 0;
	int t;
	char c = 0;
	char* sstring = string;

	do
	{
		t = 0;

		sscanf(sstring, " %d %d %n ", &k, &e, &t);
		sstring += t;

		umetniSortirano(Head, k, e);

	}while (strlen(sstring) > 1);

	return EXIT_SUCCESS;
	
}


int umetniSortirano(position Head, int k, int e)
{
	position temp = Head;
	position newEl = NULL;

	while (temp->next != NULL && temp->next->eksponent > e)
		temp = temp->next;

	if (temp->next != NULL && temp->next->eksponent == e)
		temp->next->koeficjent += k;

	else
	{
		newEl = CreateElement(k, e);
		newEl->next = temp->next;
		temp->next = newEl;
	}
	return EXIT_SUCCESS;
}

position CreateElement(int k, int e)
{
	position newEl = NULL;
	newEl = (position)malloc(sizeof(Polinom));
	if (!newEl)
	{
		perror("Neuspijesno alociranje memorije!\n");
		return NULL;
	}

	newEl->eksponent = e;
	newEl->koeficjent = k;
	

	return newEl;
}

int IspisiPolinom(position first)
{
	position temp = first;


	while (temp)
	{
		printf(" %dX^%d ", temp->koeficjent, temp->eksponent);
		if (temp->next != NULL)
			printf("+");

		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int ZbrojiPolinome(position First1, position First2, position HeadSuma)
{
	position temp1 = First1;
	position temp2 = First2;

	while (temp1)
	{
		umetniSortirano(HeadSuma, temp1->koeficjent, temp1->eksponent);
		temp1 = temp1->next;
	}
	while (temp2)
	{
		umetniSortirano(HeadSuma, temp2->koeficjent, temp2->eksponent);
		temp2 = temp2->next;
	}

	OcistiNule(HeadSuma);

	return EXIT_SUCCESS;

}

int PomnoziPolinome(position First1, position First2, position HeadProdukt)
{
	position temp1 = First1;
	position temp2 = First2;

	while (temp1)
	{
		temp2 = First2;

		while (temp2)
		{
			umetniSortirano(HeadProdukt, temp1->koeficjent * temp2->koeficjent, temp1->eksponent + temp2->eksponent);
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}

	OcistiNule(HeadProdukt);

	return EXIT_SUCCESS;

}

int OcistiNule(position Head)
{
	position p = Head;
	position temp;

	while (p->next)
	{
		if (!p->next->koeficjent)
		{
			temp = p->next;
			p->next = p->next->next;
			free(temp);
		}
		p = p->next;
	}
	return EXIT_SUCCESS;
}