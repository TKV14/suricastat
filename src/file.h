#ifndef _FILE_H
#define _FILE_H

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
	dateCell *date;

	char counter[MAXCOUNTERNAME];
	char threadName[MAXTHREADNAME];
	int64_t value;
}dataLine;

int importFile(char *filename);
int readLine(FILE *file, char *buf);
void parseDateLine(char *data, dateCell *actLine);
void parseDataLine(char *data, dataLine *actLine);
void printDate(dateCell *data);

#endif /*_FILE_H*/
