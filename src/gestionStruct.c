#include "main.h"

void newDateCell(dateCell **l)
{
	*l = (dateCell*) malloc(sizeof(dateCell));

	(*l)->day = 0;
	(*l)->month = 0;
	(*l)->year = 0;
	(*l)->hours = 0;
	(*l)->min = 0;
	(*l)->sec = 0;
	(*l)->uday = 0;
	(*l)->uhours = 0;
	(*l)->umin = 0;
	(*l)->usec = 0;
}

void newDataLine(dataLine **l)
{
	*l = (dataLine*) malloc(sizeof(dataLine));

//	(*l)->date = NULL;
	(*l)->counter[0] = '\0';
	(*l)->threadName[0] = '\0';
	(*l)->value = 0;

//	(*l)->date = (dateCell*) malloc(sizeof(dateCell));
}

void newDataList(dataList **l)
{
	*l = (dataList*) malloc(sizeof(dataList));

	(*l)->date = NULL;
	(*l)->data = NULL;
	(*l)->next = NULL;
}

void printDataList(dataList *l)
{
	while(l != NULL)
	{
		if(l->data != NULL)
			printf("%s, %s, %lld", l->data->counter, l->data->threadName, l->data->value);

		if(l->date != NULL)
			printf("  %.2d/%.2d/%.4d %.2d:%.2d:%.2d %.2d:%.2d:%.2d:%.2d",
				l->date->day,
				l->date->month,
				l->date->year,
				l->date->hours,
				l->date->min,
				l->date->sec,
				l->date->uday,
				l->date->uhours,
				l->date->umin,
				l->date->usec);

		printf("\n");

		l = l->next;
	}
}
