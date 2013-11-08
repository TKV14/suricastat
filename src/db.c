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

	return db;
}

void createTable(char *dbPath)
{
	char sqlCommand[255];
	sqlite3 *db;

	db = openDb(dbPath);

	sprintf(sqlCommand, "CREATE TABLE infos(Date DATETIME,"
						"uday INTEGER,"
						"uhours INTEGER,"
						"umin INTEGER,"
						"usec INTEGER,"
						"counter VARCHAR(%d),"
						"threadName VARCHAR(%d),"
						"value INTEGER)",
						MAXCOUNTERNAME,
						MAXTHREADNAME);

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

void insertDataList(dataList *l)
{
	int i;
	char sqlCommand[75000], tmp[150];
	dateCell *date;
	sqlite3 *db;

	i = 0;
	newDateCell(&date);
	db = openDb(DBPATH);

	while(l != NULL)
	{
		if(l->date != NULL)
			date = l->date;

		if(l->data != NULL)
		{
			if(i == 500)
			{
				strcat(sqlCommand, ";");
				sqlite3_exec(db, sqlCommand, NULL, NULL, NULL);
				i = 0;
			}

			if(i == 0)
			{
				sprintf(sqlCommand, "INSERT INTO infos VALUES ("
					"'%4d-%2d-%2d %2d:%2d:%2d',"
					"'%2d', '%2d', '%2d', '%2d', "
					"'%s', '%s', '%ld')",
					date->year,
					date->month,
					date->day,
					date->hours,
					date->min,
					date->sec,
					date->uday,
					date->uhours,
					date->umin,
					date->usec,
					l->data->counter,
					l->data->threadName,
					l->data->value);
			}
			else
			{
				sprintf(tmp, ", ("
					"'%4d-%2d-%2d %2d:%2d:%2d',"
					"'%2d', '%2d', '%2d', '%2d', "
					"'%s', '%s', '%ld')",
					date->year,
					date->month,
					date->day,
					date->hours,
					date->min,
					date->sec,
					date->uday,
					date->uhours,
					date->umin,
					date->usec,
					l->data->counter,
					l->data->threadName,
					l->data->value);


				strcat(sqlCommand, tmp);
			}

			i++;
		}

		l = l->next;
	}

	strcat(sqlCommand, ";");
	sqlite3_exec(db, sqlCommand, NULL, NULL, NULL);

	sqlite3_close(db);
}

void readDataBase(dataList **l)
{
	char tmp[255];
	dataList *ptr;
	sqlite3 *db;
	sqlite3_stmt *res;

	newDataList(l);
	ptr = *l;

	db = openDb(DBPATH);

	sqlite3_prepare_v2(db, "SELECT * FROM infos;", 255, &res, NULL);

	while(sqlite3_step(res) == SQLITE_ROW)
	{
		newDataList(&(ptr->next));
		ptr = ptr->next;
		newDateCell(&(ptr->date));
		newDataLine(&(ptr->data));

		sprintf(tmp, "%s", sqlite3_column_text(res, 5));
		strcpy(ptr->data->counter, tmp);
		sprintf(tmp, "%s", sqlite3_column_text(res, 6));
		strcpy(ptr->data->threadName, tmp);
		ptr->data->value = sqlite3_column_int64(res, 7);

		sprintf(tmp, "%s", sqlite3_column_text(res, 0));
		sscanf(tmp, "%d-%d-%d %d:%d:%d",
			&(ptr->date->year),
			&(ptr->date->month),
			&(ptr->date->day),
			&(ptr->date->hours),
			&(ptr->date->min),
			&(ptr->date->sec));

		ptr->date->uday = sqlite3_column_int(res, 1);
		ptr->date->uhours = sqlite3_column_int(res, 2);
		ptr->date->umin = sqlite3_column_int(res, 3);
		ptr->date->usec = sqlite3_column_int(res, 4);
	}
}
