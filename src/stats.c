#include "main.h"

void stats(dataList *l)
{
	int nbCounter, nbThread;
	char **counterNames = NULL;
	char **threadNames = NULL;

//	counterNames = (char**) malloc(sizeof(char*));
//	threadNames = (char**) malloc(sizeof(char*));

	nbCounter = calcNbCounter(l, &counterNames);
	nbThread = calcNbThread(l, &threadNames);

/*	printf("%d\n", nbCounter);
	for(i=0; i<nbCounter; i++)
		printf("	%s\n", counterNames[i]);

	printf("%d\n", nbThread);
	for(i=0; i<nbThread; i++)
		printf("	%s\n", threadNames[i]);
*/

	calcNbDropForCounter(l, counterNames[0]);
	calcNbDropForCounter(l, counterNames[1]);

	printf("sec: %d\n", clacSecondeInRun(l));
}

int64_t calcNbDropForCounter(dataList *l, char *counterName)
{
	int64_t count;

	count = 0;

	while(l != NULL)
	{
		if(l->data != NULL)
			if(strcmp(l->data->counter, counterName) == 0)
				count += l->data->value;

		l = l->next;
	}

	return count;
}

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
			else if(compareUDateCell(l->date, d) == -1)
			{
				d = l->date;
				count ++;
			}
		}

		l = l->next;
	}

	return count;
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
