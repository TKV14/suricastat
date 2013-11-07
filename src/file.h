#ifndef _GESTIONSTRUCT_H
#include "gestionStruct.h"
#endif

#ifndef _FILE_H
#define _FILE_H

#define NBTOINSERT 2

int importFile(char *filename);
int readLine(FILE *file, char *buf);
void parseDateLine(char *data, dateCell *actLine);
void parseDataLine(char *data, dataLine *actLine);
void printDate(dateCell *data);
void insertToList(dataList **l, dataLine *actLine);

#endif /*_FILE_H*/
