#include "main.h"

int importFile(char *filename)
{
	/*
		Import un fichier
		Renvoie -1 en cas d'erreur
		Renvoie 1 en cas de succes
	*/
	int retour, nbReadLine;
	char buf[255], insertLine[5000000];
	FILE *filelog = NULL;
	dataLine *actLine = NULL;
	dataList *l = NULL;
	dataList *ptr = NULL;

	retour = 0;
	nbReadLine = 0;
	memset(insertLine, '\0', 5000000);
	sprintf(insertLine, "INSERT INTO infos VALUES ('test', 'test', '10')\n");

	newDataList(&l); 
	newDataLine(&actLine);

	filelog = fopen(filename, "r");
	if(filelog == NULL)
	{
		fprintf(stderr, "Fichier non ouvert: %s\n", strerror(errno));
		return -1;
	}

	ptr = l;

	while((retour = readLine(filelog, buf)) != -1)
	{
		nbReadLine ++;

		switch(retour)
		{
			case 1:
				parseDataLine(buf, actLine);
				insertToList(&ptr, actLine);
				break;
			case 2:
				newDateCell(&(ptr->date));
				parseDateLine(buf, ptr->date);
				newDataList(&(ptr->next));
				ptr = ptr->next;
				break;
			default:
				break;
		}
	}

	free(actLine);

	insertDataList(l);

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
}

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

void insertToList(dataList **l, dataLine *actLine)
{
	int i;
	char **toInsert;

	toInsert = malloc(sizeof(char*) * NBTOINSERT);
	for(i=0; i<NBTOINSERT; i++)
		toInsert[i] = malloc(sizeof(char)*MAXCOUNTERNAME);

	sprintf(toInsert[0], "capture.kernel_packets");
	sprintf(toInsert[1], "capture.kernel_drops");

	for(i=0; i<NBTOINSERT; i++)
	{
		if(strcmp(toInsert[i], actLine->counter) == 0)
		{
			newDataList(&((*l)->next));
			*l = (*l)->next;
			newDataLine(&((*l)->data));

			strcpy((*l)->data->counter, actLine->counter);
			strcpy((*l)->data->threadName, actLine->threadName);
			(*l)->data->value = actLine->value;
		}
	}
}
