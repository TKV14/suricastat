#ifndef _STATS_H
#define _STATS_H

#define SEC 1
#define MIN 60*SEC
#define HOUR 60*MIN
#define DAY 24*HOUR

void stats(dataList *l);
int64_t calcNbDropForCounter(dataList *l, char *counterName);
int clacNbRun(dataList *l);
int nbSecondeInRun(dataList *l, int run);
int calcNbThread(dataList *l, char ***threadNames);
int calcNbCounter(dataList *l, char ***counterName);

#endif /*_STATS_H*/
