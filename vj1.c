#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_NAME 128
#define MAX_BODOVI 100

typedef struct {

	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	double bodovi;

} student;

int procitajbrred(char* nazivdat);
student* alocirajIucitajdat(char* nazivdat, int brst);
double maxbod(student* studenti, int brst);
void ispisStudenata(student* studenti, int brst);

int main(int argc, char* argv[])
{
	int brst = 0;
	char* nazivdat = NULL;
	student* studenti = NULL;

	if (argc < 2)
	{
		printf("Ime datoteke datoteke se ne nalazi unutar command line argumenata.\n");
		return -1;
	}

	nazivdat = argv[1];

	brst = procitajbrred(nazivdat);

	if (brst <= 0)
	{
		printf("Datoteka je prazna te se ne mogu ucitati podaci.\n");
		return -1;
	}

	studenti = alocirajIucitajdat(nazivdat, brst);

	ispisStudenata(studenti, brst);

	free(studenti);
	return 0;
}

int procitajbrred(char* nazivdat)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(nazivdat, "r");

	if (!datoteka)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}

	fclose(datoteka);
	return brojac;
}

student* alocirajIucitajdat(char* nazivdat, int brst)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	student* studenti = NULL;

	datoteka = fopen(nazivdat, "r");

	studenti = (student*)malloc(brst * sizeof(student));

	if (!datoteka || !studenti)
	{
		printf("Greska pri otvaranju datoteke ili alociranju studenata!\n");
		return NULL;
	}

	for (int i = 0; i < brst; i++)
	{
		fscanf(datoteka, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);
	return studenti;
}

double maxbod(student* studenti, int brst)
{
	int i = 0;
	double maxbrbod = 0;

	maxbrbod = studenti[0].bodovi;

	for (i = 0; i < brst; i++)
		if (studenti[i].bodovi > maxbrbod)
			maxbrbod = studenti[i].bodovi;

	return maxbrbod;
}

void ispisStudenata(student* studenti, int brst)
{
	int i = 0;
	double maxbrbod = 0;

	maxbrbod = maxbod(studenti, brst);

	printf("%-25s%-25s%-25s%-25s\n", "IME", "PREZIME", "APSOLUTAN BROJ BODOVA", "RELATIVAN BROJ BODOVA");

	for (i = 0; i < brst; i++)
		printf("%-25s%-25s%-25.2lf%-25.2lf\n",
			studenti[i].ime,
			studenti[i].prezime,
			studenti[i].bodovi / MAX_BODOVI * 100,
			studenti[i].bodovi / maxbrbod * 100);
}