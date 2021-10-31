#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAX 50
#define MAXL 1024


struct _person;
typedef struct _person* Position;
typedef struct _person {

	char name[MAX];
	char surname[MAX];
	int bYear;
	Position next;

}Person;

typedef struct {
	char name[MAX];
	char surname[MAX];
	int bYear;
	Position next;
} Sortirana;

int PreppandList(Position Head, char* name, char* surname, int bYear);
Position CreatePer(char* name, char* surname, int bYear);
int InsertAfter(Position position, Position person);
int PrintList(Position first);
int AppandList(Position Head, char* name, char* surname, int bYear);
Position FindLast(Position Head);
Position FindBySurname(Position first, char* surname);
Position deleteEl(Position head, char* surname);
Position FindBefore(Position first, char* surname);
int AddAfterEl(Position Head, char* sur, char* name, char* surname, int bYear);
int AddBeforeEl(Position Head, char* sur, char* name, char* surname, int bYear);
int InsertBefore(Position position, Position person, char* sur);
int printInDat(Position first, char* nazivDat);
int ProcitajIzDat(char* nazivDat);
void InsertSort(Position head, char* name, char* surname, int bYear);
Position FindPrev(Position head, Position el);
int IspisDatoteke(char* imeDat);



int main(int argc, char** argv)
{
	Person Head = { .name = {0}, .surname = {0}, .bYear = 0, .next = NULL };
	Sortirana head = { .name = {0}, .surname = {0}, .bYear = 0, .next = NULL };
	Position p = &Head;
	Position s = &head;
	Position temp = NULL;
	char name[MAX], surname[MAX], sur[MAX];
	int bYear, br, odabir;

	printf("IZBORNIK\n\nIzaberite opciju: \n");
	printf("1 -> Dodaj osobu na pocetak liste.\n");
	printf("2 -> Dodaj osobu na kraj liste.\n");
	printf("3 -> Ispisi listu.\n");
	printf("4 -> Pronadi osobu po prezimenu.\n");
	printf("5 -> Obrisi osobu iz liste.\n");
	printf("6 -> Dodaj osobu iza odredene osobe.\n");
	printf("7 -> Dodaj osobu ispred odredene osobe.\n");
	printf("8 -> Upisi listu u datoteku.\n");
	printf("9 -> Ispisi listu iz datoteke.\n");
	printf("10 -> Ispisi sortiranu listu .\n");
	printf("0 -> Izadi iz izbornika.\n");

	printf("\nVas odabir: ");
	scanf("%d", &odabir);


	while (odabir)
	{
		
		switch (odabir)
		{
		case 1:
			printf("\nUnesite podatke ososbe: ");
			scanf("%s", name);
			scanf("%s", surname);
			scanf("%d", &bYear);
			if (PreppandList(p, name, surname, bYear) == 1)
				printf("Neuspijesno dodavanje elemenata!\n");
			InsertSort(s, name, surname, bYear);
			break;

		case 2:
			printf("\nUnesite osobu: ");
			scanf("%s", name);
			scanf("%s", surname);
			scanf("%d", &bYear);
			if (AppandList(p, name, surname, bYear) == 1)
				printf("\nNeuspijesno dodavanje elemenata!\n");
			InsertSort(s, name, surname, bYear);
			break;

		case 3:
			printf("\nIspis liste: \n");
			PrintList(p->next);
			break;

		case 4:
			printf("\nUnesite prezime: ");
			scanf("%s", surname);
			temp = FindBySurname(p, surname);
			if (temp)
				printf("\nOsoba:\n %s %s %d", temp->name, temp->surname, temp->bYear);
			else
				printf("\nOsobe nema na listi.\n");
			break;

		case 5:
			printf("\nKoji element zelite obrisati?\n");
			scanf("%s", surname);
			deleteEl(p, surname);
			deleteEl(s, surname);
			break;

		case 6:
			printf("\nUnesite prezime osobe iza koje zelite dodati novi element:");
			scanf("%s", sur);
			printf("\nUnesite podatke o osobi: ");
			scanf("%s", name);
			scanf("%s", surname);
			scanf("%d", &bYear);
			if (AddAfterEl(p, sur, name, surname, bYear) == 1)
				printf("\nNeuspiješno dodavanje elementa!\n");
			InsertSort(s, name, surname, bYear);
			break;

		case 7:
			printf("\nUnesite prezime osobe ispred koje zelite dodati novi element:");
			scanf("%s", sur);
			printf("\nUnesite podatke o osobi: ");
			scanf("%s", name);
			scanf("%s", surname);
			scanf("%d", &bYear);
			if (AddBeforeEl(p, sur, name, surname, bYear) == 1)
				printf("Neuspiješno dodavanje elementa!\n");
			InsertSort(s, name, surname, bYear);
			break;

		case 8:
			printInDat(p->next, "lista.txt");
			break;

		case 9:

			br = ProcitajIzDat("lista.txt");
			IspisDatoteke("lista.txt");

			break;

		case 10:
			printf("Ispis sortirane liste: \n");
			PrintList(s->next);
			break;

		default:
			printf("\nKrivi unos!\n");
			break;

		}
		printf("\nVas odabir: ");
		scanf("%d", &odabir);
	}

	
	
	return EXIT_SUCCESS;
}


int PreppandList(Position Head, char* name, char* surname, int bYear)
{
	Position newPer = NULL;
	newPer = CreatePer(name, surname, bYear);
	if (!newPer)
		return 1;

	InsertAfter(Head, newPer);
	
	return EXIT_SUCCESS;

}

Position CreatePer(char* name, char* surname, int bYear)
{
	Position newPer = NULL;
	newPer = (Position)malloc(sizeof(Person));
	if (!newPer)
	{
		perror("Cant allocate memory!\n");
		return NULL;
	}
	strcpy(newPer->name, name);
	strcpy(newPer->surname, surname);
	newPer->bYear = bYear;
	newPer->next = NULL;

	return newPer;

}

int InsertAfter(Position position, Position person)
{
	person->next = position->next;
	position->next = person;

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;

	while (temp)
	{
		printf("%s %s %d\n", temp->surname, temp->name, temp->bYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;

}

int AppandList(Position Head, char* name, char* surname, int bYear)
{
	
	Position last = NULL;
	Position newPer = NULL;

	newPer = CreatePer(name, surname, bYear);
	if (!newPer)
		return 1;

	last = FindLast(Head);

	InsertAfter(last, newPer);

	return EXIT_SUCCESS;

	

	

}

Position FindLast(Position Head) 
{
	Position temp = Head;

	while (temp->next)
	{
		temp = temp->next;
	}

	return temp;

}

Position FindBySurname(Position first, char* surname)
{
	Position temp = first;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
			return temp;

		temp = temp->next;

	}

	return NULL;
}

Position deleteEl(Position head, char* surname)
{
	Position before = NULL;
	Position elem = NULL;

	before = FindBefore(head, surname);
	if (before == 0)
		printf("Osobe nema na listi!\n");
	else
	{
		elem = before->next;
		before->next = elem->next;
	}

	return NULL;
}

Position FindPrev(Position head, Position el)
{
	Position temp = head;

	while (temp->next != el)
		temp = temp->next;

	return temp;

	
}

int AddAfterEl(Position Head, char* sur, char* name, char* surname, int bYear)
{
	Position newP = NULL;
	Position position = NULL;

	newP = CreatePer(name, surname, bYear);
	if (!newP)
		return 1;

	
	if (FindBySurname(Head->next, sur) != NULL)
		position = FindBySurname(Head->next, sur);
	else
		return 1;

		
	InsertAfter(position, newP);

}

int AddBeforeEl(Position Head, char* sur, char* name, char* surname, int bYear)
{
	Position newPer = NULL;
	Position position = NULL;
	

	newPer = CreatePer(name, surname, bYear);
	if (!newPer)
		return 1;


	if (FindBefore(Head, sur) != NULL)
		position = FindBefore(Head, sur);
	else
		return 1;



	InsertAfter(position, newPer);
		
}

int InsertBefore(Position position, Position person, char* sur)
{
	
	
	person->next = position->next;
	position->next = person;

	return EXIT_SUCCESS;
}

int printInDat(Position first, char* nazivDat)
{
	FILE* fp = NULL;
	fp = fopen(nazivDat, "w");
	Position temp = first;
	if (!fp)
	{
		printf("Neuspijesno otvaranje datoteke!\n");
		return 1;
	}

	while (temp)
	{
		fprintf(fp, "%s %s %d\n", temp->name, temp->surname, temp->bYear);
		temp = temp->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int ProcitajIzDat(char* nazivDat)
{
	FILE* fp = NULL;
	char niz[MAX] = { 0 };
	int br = 0;
	fp = fopen(nazivDat, "r");
	if (!fp)
	{
		printf("Neuspijesno otvaranje datoteke!\n");
		return 1;
	}

	while (!(feof(fp)))
	{
		fgets(niz, MAXL, fp);
		br++;
	}
	fclose(fp);

	return br;

}





Position FindBefore(Position first, char* surname)
{
	Position temp = first;

	for (temp; temp->next; temp = temp->next) {
		if (!strcmp(surname, temp->next->surname)) {
			return temp;
		}
	}

	return NULL;

}

void InsertSort(Position head, char* name, char* surname, int bYear)
{
	Position person = NULL;

	person = CreatePer(name, surname, bYear);
	if (!person)
		return 1;
	Position before = NULL;
	Position temp = head->next;

	if (!temp)
	{
		InsertAfter(head, person);
	}
	else
	{
		while (temp && strcmp(surname, temp->surname))
			temp = temp->next;

		before = FindPrev(head, temp);
		InsertAfter(before, person);
	}

	return EXIT_SUCCESS;
}

int IspisDatoteke(char* imeDat)
{
	FILE* fp = NULL;
	char buffer;
	fp = fopen(imeDat, "r");
	if (!fp)
		return 1;

	while (!feof(fp))
	{
		buffer = fgetc(fp);
		printf("%c", buffer);
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

