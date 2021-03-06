#include "main.h"

void stats(dataList *l)
{
	int i, j, nbCounter, nbThread, nbRun;
	int64_t drop1, drop2, nbDrop1Run, nbDrop2Run;
	char **counterNames = NULL;
	char **threadNames = NULL;

	counterNames = (char**) malloc(sizeof(char*));
	threadNames = (char**) malloc(sizeof(char*));

	nbCounter = calcNbCounter(l, &counterNames);
	nbThread = calcNbThread(l, &threadNames);
	nbRun = clacNbRun(l);
	nbDrop1Run = 0;
	nbDrop2Run = 0;

	printf("Nombre de run: %d\n", nbRun);
	printf("Nombre de thread: %d\n", nbThread);
	printf("Nombre de compteur: %d\n", nbCounter);

	for(i=0; i<nbRun; i++)
	{
		printf("  Run %d\n", i);

		for(j=0; j<nbThread; j++)
		{
			drop1 = calcNbDropForCounter(l, counterNames[0], threadNames[j], i+1);
			drop2 = calcNbDropForCounter(l, counterNames[1], threadNames[j], i+1);

			printf("    %16s: %16lld | %16lld | %f\n", threadNames[j], drop1, drop2, (float)drop2/(float)drop1);

			nbDrop1Run += drop1;
			nbDrop2Run += drop2;
		}

		printf("_______________________________________________________________________________\n");
		printf("  %18s: %16lld | %16lld | %f\n", "TOTAL", nbDrop1Run, nbDrop2Run, (float)nbDrop2Run/(float)nbDrop1Run);
		printf("    Moyenne paquets/secondes: %10.1f | Moyenne drops/secondes: %10.1f\n\n",
			(float)nbDrop1Run/(float)nbSecondeInRun(l, i),
			(float)nbDrop2Run/(float)nbSecondeInRun(l, i));
	}
}

int64_t calcNbDropForCounter(dataList *l, char *counterName, char *threadName, int run)
{
	int64_t count, numRun;
	dateCell *d = NULL;

	count = 0;
	numRun = 0;

	while(l != NULL)
	{
		if(l->data != NULL)
		{
			if(l->date != NULL)
			{
				if(d == NULL)
				{
					d = l->date;
					numRun++;
				}

				if(compareUDateCell(l->date, d) == -1)
				{
					d = l->date;
					numRun ++;
				}
				else
					d = l->date;

				if(run == numRun)
					if(strcmp(l->data->threadName, threadName) == 0)
						if(strcmp(l->data->counter, counterName) == 0)
							count = l->data->value;
			}
		}

		l = l->next;
	}

	return count;
}
/*
int64_t calcNbDropForCounter(dataList *l, char *counterName, int run)
{
	int64_t count, numRun;
	dateCell *d = NULL;

	count = 0;
	numRun = 0;

	while(l != NULL)
	{
		if(l->data != NULL)
		{
			if(l->date != NULL)
			{
				if(d == NULL)
				{
					d = l->date;
					numRun++;
				}

				if(compareUDateCell(l->date, d) == -1)
				{
					d = l->date;
					numRun ++;
				}
				else
					d = l->date;

				if(run == numRun)
					if(strcmp(l->data->counter, counterName) == 0)
						count += l->data->value;
			}
		}

		l = l->next;
	}

	return count;
}
*/
int clacNbRun(dataList *l)
{
	int count;
	dateCell *d = NULL;

	count = 0;

	while(l != NULL)
	{
		if(l->date != NULL)
		{
			if(d == NULL)
			{
				d = l->date;
				count ++;
			}

			if(compareUDateCell(l->date, d) == -1)
			{
				d = l->date;
				count ++;
			}
			else
				d = l->date;
		}

		l = l->next;
	}

	return count;
}

int nbSecondeInRun(dataList *l, int run)
{
	int count;
	dateCell *d = NULL;

	count = 0;

	while(l != NULL)
	{
		if(l->date != NULL)
		{
			if(d == NULL)
			{
				d = l->date;
				count ++;
			}

			if(compareUDateCell(l->date, d) == -1)
			{
				if(count == run)
					break;

				d = l->date;
				count ++;
			}
			else
				d = l->date;
		}

		l = l->next;
	}

	return (d->usec*SEC)+
		(d->umin*MIN)+
		(d->uhours*HOUR)+
		(d->uday*DAY);
}

int calcNbThread(dataList *l, char ***threadNames)
{
	int i, count, test;

	count = 0;

	while(l != NULL)
	{
		if(l->data != NULL)
		{
			if(count == 0)
			{
				count++;

				*threadNames = (char**) malloc(sizeof(char*) * count);
				(*threadNames)[count-1] = (char*) malloc(sizeof(char) * MAXTHREADNAME);
				memset((*threadNames)[count-1], '\0', MAXTHREADNAME);

				strcpy((*threadNames)[count-1], l->data->threadName);
			}

			for(i=0, test=0; i<count; i++)
				if(strcmp((*threadNames)[i], l->data->threadName) == 0)
					test = 1;

			if(test == 0)
			{
				count++;

				*threadNames = (char**) realloc((*threadNames), sizeof(char*) * count);
				(*threadNames)[count-1] = (char*) malloc(sizeof(char) * MAXTHREADNAME);
				memset((*threadNames)[count-1], '\0', MAXTHREADNAME);

				strcpy((*threadNames)[count-1], l->data->threadName);
			}
		}

		l = l->next;
	}

	return count;
}

int calcNbCounter(dataList *l, char ***counterName)
{
	int i, count, test;

	count = 0;

	while(l != NULL)
	{
		if(l->data != NULL)
		{
			if(count == 0)
			{
				count++;

				*counterName = (char**) malloc(sizeof(char*) * count);
				(*counterName)[count-1] = (char*) malloc(sizeof(char) * MAXCOUNTERNAME);
				memset((*counterName)[count-1], '\0', MAXCOUNTERNAME);

				strcpy((*counterName)[count-1], l->data->counter);
			}

			for(i=0, test=0; i<count; i++)
				if(strcmp((*counterName)[i], l->data->counter) == 0)
					test = 1;

			if(test == 0)
			{
				count++;

				*counterName = (char**) realloc((*counterName), sizeof(char*) * count);
				(*counterName)[count-1] = (char*) malloc(sizeof(char) * MAXCOUNTERNAME);
				memset((*counterName)[count-1], '\0', MAXCOUNTERNAME);

				strcpy((*counterName)[count-1], l->data->counter);
			}
		}

		l = l->next;
	}

	return count;
}
