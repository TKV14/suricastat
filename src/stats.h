#ifndef _STATS_H
#define _STATS_H

void stats(dataList *l);
int64_t calcNbDropForCounter(dataList *l, char *counterName);
int clacSecondeInRun(dataList *l);
int calcNbThread(dataList *l, char ***threadNames);
int calcNbCounter(dataList *l, char ***counterName);

#endif /*_STATS_H*/
