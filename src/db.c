#include "main.h"

void openDb()
{
	char dbPath[] = "/home/foo/Documents/Prog/C/suricatastat/test.db";
	sqlite3 *db;

	if(sqlite3_open(dbPath, &db) == 1)
	{
		fprintf(stderr, "Can't open database\n");
		return;
	}

	printf("Database open\n");

	sqlite3_close(db);
}
