#include "main.h"

int importFile(char *filename)
{
	/*
		Import un fichier
		Renvoie -1 en cas d'erreur
		Renvoie 1 en cas de succes
	*/
	int retour, nbReadLine;
	char buf[255];
	FILE *filelog = NULL;
	dataLine *actLine = NULL;

	retour = 0;
	nbReadLine = 0;

	actLine = (dataLine*) malloc(sizeof(dataLine));
	if(actLine == NULL)
	{
		fprintf(stderr, "Allocation Failed (dataLine)\n");
		return -1;
	}
	actLine->date = (dateCell*) malloc(sizeof(dateCell));
	if(actLine->date == NULL)
	{
		fprintf(stderr, "Allocation Failed (date)\n");
		return -1;
	}

	filelog = fopen(filename, "r");
	if(filelog == NULL)
	{
		fprintf(stderr, "Fichier non ouvert: %s\n", strerror(errno));
		return -1;
	}

	while((retour = readLine(filelog, buf)) != -1)
	{
		nbReadLine ++;

		switch(retour)
		{
			case 1:
				parseDataLine(buf, actLine);
				break;
			case 2:
				parseDateLine(buf, actLine->date);
				break;
			default:
				break;
		}
	}

	free(actLine->date);
	free(actLine);

	return 1;
}

int readLine(FILE *file, char *data)
{
	/*
		Lit une ligne du fichier
		Renvoie 1 pour une ligne de donnee
		Renvoie 2 pour une ligne de date
		Renvoie 3 pour une ligne de Titre
		Renvoie 4 pour une ligne de "-"
(a faire)	Renvoie 0 pour une ligne non authentifiee
		Renvoie -1 si la fin du fichier est atteinte
	*/

	char buf[255];
	memset(buf, '\0', 255);

	if(fgets(buf, 255, file) == NULL)
		return -1;

	strncpy(data, buf, 255);

	if(buf[0] == '-')
		return 4;

	if(strstr(buf, "Date: ") != NULL)
		return 2;

	if(strstr(buf, "Counter") != NULL)
		return 3;

	return 1;
}

void parseDateLine(char *data, dateCell *actDate)
{
	sscanf(data, "Date: %d/%d/%d -- %d:%d:%d (uptime: %dd, %dh %dm %ds)",
			&(actDate->month),
			&(actDate->day),
			&(actDate->year),
			&(actDate->hours),
			&(actDate->min), 
			&(actDate->sec),
			&(actDate->uday),
			&(actDate->uhours),
			&(actDate->umin),
			&(actDate->usec)
	      );
}

void parseDataLine(char *data, dataLine *actLine)
{
	sscanf(data, "%s | %s | %lld",
			actLine->counter,
			actLine->threadName,
			&(actLine->value)
		);

/*	printf("%s | %s | %ld\n",
			actLine->counter,
			actLine->threadName,
			actLine->value
		);
*/}

void printDate(dateCell *date)
{
	printf("%.2d/%.2d/%.2d %.2d:%.2d:%.2d ,%.2d, %.2d %.2d %.2d\n",
			date->day,
			date->month,
			date->year,
			date->hours,
			date->min, 
			date->sec,
			date->uday,
			date->uhours,
			date->umin,
			date->usec
	      );
}
