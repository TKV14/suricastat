#include "main.h"

int nbThread(dataList *l)
{
	int i, count, test;
	char **threadNames = NULL;

	count = 0;
//	threadNames = (char **) malloc(sizeof(char*) * 1);
//	threadNames[0] = (char *) malloc(sizeof(char) * MAXTHREADNAME);
//	memset(threadNames, '\0', MAXTHREADNAME);

	while(l != NULL)
	{
		if(l->data != NULL)
		{
			if(count == 0)
			{
				count++;

				threadNames = (char **) malloc(sizeof(char*) * count);
				threadNames[count-1] = (char *) malloc(sizeof(char) * MAXTHREADNAME);
				memset(threadNames[count-1], '\0', MAXTHREADNAME);

				strcpy(threadNames[count-1], l->data->threadName);
			}

			for(i=0, test=0; i<count; i++)
				if(strcmp(threadNames[i], l->data->threadName) == 0)
					test = 1;

			if(test == 0)
			{
				count++;

				threadNames = (char **) realloc(threadNames, sizeof(char*) * count);
				threadNames[count-1] = (char *) malloc(sizeof(char) * MAXTHREADNAME);
				memset(threadNames[count-1], '\0', MAXTHREADNAME);

				strcpy(threadNames[count-1], l->data->threadName);
			}
		}

		l = l->next;
	}

	return count;
}
