#ifndef _GESTIONSTRUCT_H
#define _GESTIONSTRUCT_H

#define MAXTHREADNAME 255
#define MAXCOUNTERNAME 255

typedef struct _dateCell
{
	int day;
	int month;
	int year;
	int hours;
	int min;
	int sec;
	int uday;
	int uhours;
	int umin;
	int usec;
}dateCell;

typedef struct _dataLine
{
//	dateCell *date;

	char counter[MAXCOUNTERNAME];
	char threadName[MAXTHREADNAME];
	int64_t value;
}dataLine;

typedef struct _dataList
{
	dateCell *date;
	dataLine *data;
	struct _dataList *next;
}dataList;

void newDataLine(dataLine **l);
void newDateCell(dateCell **l);
void newDataList(dataList **l);
void printDataList(dataList *l);
int convertUDateToSec(dateCell *d);
int compareUDateCell(dateCell *d1, dateCell *d2);

#endif /*_GESTIONSTRUT_H*/
