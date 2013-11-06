#include "main.h"

sqlite3 *openDb(char *dbPath)
{
//	char dbPath[] = "/home/foo/Documents/Prog/C/suricatastat/test.db";
	sqlite3 *db;

	if(sqlite3_open(dbPath, &db) == 1)
	{
		fprintf(stderr, "Can't open database\n");
		return NULL;
	}

//	printf("Database open\n");

	return db;

//	sqlite3_close(db);
}

void createTable(char *dbPath)
{
	char sqlCommand[255];
	sqlite3 *db;

	db = openDb(dbPath);

	sprintf(sqlCommand, "CREATE TABLE infos(counter VARCHAR(%d), threadName VARCHAR(%d), value INTEGER)",
		MAXCOUNTERNAME, MAXTHREADNAME);

	sqlite3_exec(db, sqlCommand, NULL, NULL, NULL);

	sqlite3_close(db);
}

void insertTable(char *counter, char *threadName, int value)
{
	char sqlCommand[512];
	sqlite3 *db;

	db = openDb(DBPATH);

	sprintf(sqlCommand, "INSERT INTO infos VALUES('%s', '%s', '%d');", counter, threadName, value);

	sqlite3_exec(db, sqlCommand, NULL, NULL, NULL);

	sqlite3_close(db);
}
