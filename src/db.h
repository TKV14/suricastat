#ifndef _DB_H
#define _DB_H

#include <sqlite3.h>

#define DBPATH "../test.db"

sqlite3 *openDb(char *dbPath);
void createTable(char *db);
void insertTable(char *counter, char *threadName, int value);

#endif
