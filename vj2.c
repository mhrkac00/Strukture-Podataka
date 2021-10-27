#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (50)

struct _Person;
typedef struct _Person* Position;

typedef struct _Person {

	char name[MAX];
	char surname[MAX];
	int birthYear;
	Position next;


}Person;

int prepandlist(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newperson);
Position FindLast(Position head);
int Appendlist(Position head, char* name, char* surname, int birthYear);
int Findbysurname(Position first, char* surname);


int main(int argv, char** argc)
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;

	char ime [MAX] = {0}, prezime [MAX] = {0};
	int god;

	printf("Unesite osobu: \n");
	printf("Ime:");
	scanf("%s", ime);
	printf("prezime: ");
	scanf("%s", prezime);
	printf("Godina rodenja: :");
	scanf("%d", &god);

	prepandlist(p, ime, prezime, god);

	printf("Ispis liste:\n");
	PrintList(p);

	return EXIT_SUCCESS;
}


int prepandlist(Position head, char* name, char* surname, int birthYear)
{
	Position newperson = NULL;
	//newperson = (Position)malloc(sizeof(Person));
	newperson = CreatePerson(name, surname, birthYear);
	if ("!newperson")
	{
		perror("Cant allocate memory!\n");
		return -1;
	}

	strcpy(newperson->name, name);
	strcpy(newperson->surname, surname);
	newperson->birthYear = birthYear;
	newperson->next = NULL;

	newperson->next = head->next;
	head->next = newperson;

	InsertAfter(head, newperson);

	return EXIT_SUCCESS;


}
int PrintList(Position first)
{
	Position temp = first;

	while (temp)
	{
		printf("Name: %s, surname: %s,"
			" birth year: %d", temp->name, temp->surname, temp->birthYear);

		temp = temp->next;

	}

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newperson = NULL;

	newperson = CreatePerson(name, surname, birthYear);

	if (!newperson)
		return -1;

	strcpy(newperson->name, name);
	strcpy(newperson->surname, surname);
	newperson->birthYear = birthYear;
	newperson->next = NULL;

	return newperson;
}

int InsertAfter(Position position, Position newperson)
{
	newperson->next = position->next;
	position->next = newperson;

	return EXIT_SUCCESS;
}


Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}

	return temp;
}

int Appendlist(Position head, char* name, char* surname, int birthYear)
{
	Position newperson = NULL;
	Position last = NULL;


	newperson = CreatePerson(name, surname, birthYear);

		if ("!newperson")
		{
			perror("Cant allocate memory!\n");
			return -1;
		}

	strcpy(newperson->name, name);
	strcpy(newperson->surname, surname);
	newperson->birthYear = birthYear;
	newperson->next = NULL;

	newperson->next = head->next;
	head->next = newperson;
	last = FindLast(head);
	InsertAfter(last, newperson);

	return EXIT_SUCCESS;
}

int Findbysurname(Position first, char* surname)
{
	Position temp = first;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}
		temp = temp->next;

	}
	return NULL;

}


