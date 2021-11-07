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
int DeleteAfter(position previous);
int OcistiMemoriju(position Head);

int main(int argc, char** argv)
{

	Polinom Head1 = { .koeficjent = 0, .eksponent = 0, .next = NULL};
	Polinom Head2 = { .koeficjent = 0, .eksponent = 0, .next = NULL };
	Polinom HeadSuma = { .koeficjent = 0, .eksponent = 0, .next = NULL };
	Polinom HeadProdukt = { .koeficjent = 0, .eksponent = 0, .next = NULL };

	position p1 = &Head1;
	position p2 = &Head2;
	position pS = &HeadSuma;
	position pP = &HeadProdukt;



	
	if (ProcitajIzDat(p1, p2, "polinomi.txt") == EXIT_SUCCESS)
	{
		printf("Prvi polinom:\t");
		IspisiPolinom(p1->next);

		printf("\n\nDrugi polinom:\t");
		IspisiPolinom(p2->next);

		ZbrojiPolinome(p1->next, p2->next, pS);
		printf("\n\nZbroj polinoma:\t");
		IspisiPolinom(pS->next);

		PomnoziPolinome(p1->next, p2->next, pP);
		printf("\n\nProdukt polinoma:   ");
		IspisiPolinom(pP->next);
	}

	OcistiMemoriju(p1);
	OcistiMemoriju(p2);
	OcistiMemoriju(pS);
	OcistiMemoriju(pP);
	
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
	int t = 0;
	char* sstring = string;
	int check = 0;

	while (strlen(sstring) > 0)
	{

		t = 0;

		check = sscanf(sstring, " %d %d %n ", &k, &e, &t);
		if (check != 2)
			break;
		sstring += t;

		umetniSortirano(Head, k, e);
		
	}

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
		if (temp->eksponent == 0)
			printf(" %d ", temp->koeficjent);
		else if (temp->eksponent == 1 && temp->koeficjent == 1)
			printf(" X ");
		else if (temp->eksponent == 1)
			printf(" %dX ", temp->koeficjent);
		else if (temp->koeficjent == 1)
			printf(" X%d ", temp->eksponent);
		else
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

int DeleteAfter(position previous)
{
	position temp = NULL;

	temp = previous->next;
	previous->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int OcistiMemoriju(position Head)
{
	position temp = Head;

	while (temp->next)
	{
		DeleteAfter(temp);
	}

	return EXIT_SUCCESS;
}