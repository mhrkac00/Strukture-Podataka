#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXL 1024
#define MAX 50

typedef struct {

	char ime[MAX];
	char prezime[MAX];
	int bodovi;

}Studenti;


int ProcitajRedke(char* nazivDat);
Studenti* alokacirajMemoriju(int brst);
int MaxBodovi(int brBod, Studenti* student);

int main(int argc, char** argv)
{
	Studenti* student = NULL;
	int brst = 0, i, ab;
	double rb;
	int max;

	if (ProcitajRedke("studenti.txt") != -1)
		brst = ProcitajRedke("studenti.txt");
	else
		return 0;

	student = alokacirajMemoriju(brst, "studenti.txt");

	if (!student)
		return 0;

	max = MaxBodovi(brst, student);

	for (i = 0; i < brst; i++)
	{
		ab = student[i].bodovi;
		rb = (double)ab / max;

		printf("%s\t%s\tAB: %d\tRB: %.2lf\n", student[i].ime, student[i].prezime, ab, rb);
	}


	
	return EXIT_SUCCESS;
}

int ProcitajRedke(char* nazivDat)
{
	FILE* fp = NULL;
	int br = 0;
	char string[MAXL] = { 0 };

	fp = fopen(nazivDat, "r");

	if (!fp)
	{
		printf("neuspijesno otvaranje datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fgets(string, MAXL, fp);
		br++;
	}

	fclose(fp);

	return br;
}

Studenti* alokacirajMemoriju(int brst, char* nazivDat)
{
	FILE* fp;
	Studenti* Student = NULL;
	char string[MAXL] = { 0 };
	int br = 0;

	Student = (Studenti*)malloc(brst * sizeof(Studenti));

	if (!Student)
	{
		perror("Ne mozemo alocirati memoriju!\n");
		free(Student);
		return -1;
	}

	fp = fopen(nazivDat, "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", Student[br].ime, Student[br].prezime, &Student[br].bodovi);
			br++;
	}

	fclose(fp);

	return Student;
}

int MaxBodovi(int brst, Studenti* student)
{
	int i, max = 0;

	for (i = 0; i < brst; i++)
		if (student[i].bodovi > max)
			max = student[i].bodovi;

	return max;
}