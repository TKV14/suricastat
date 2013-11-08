#include "main.h"

int main(int argc, char *argv[])
{
	int option;
	char opt;

	option = 0;

	while((opt = getopt(argc, argv, "hcdf:i:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				displayHelp();
				option = 1;
				break;
			case 'c':
				createDataBase();
				option = 1;
				break;

			case 'd':
				dropDataBase();
				option = 1;
				break;

			case 'f':
				launchStatsFile(optarg);
				option = 1;
				break;

			case 'i':
				launchImport(optarg);
				break;
		}
	}

	if(option == 0)
		launchStats();

	return 0;
}

void launchStats()
{
	dataList *l = NULL;

	readDataBase(&l);
	stats(l);

	freeDataList(l);
}

void launchStatsFile(char *log)
{
	dataList *l = NULL;

	importFile(log, &l);
	stats(l);

	freeDataList(l);
}

void launchImport(char *log)
{
	dataList *l = NULL;

	importFile(log, &l);
	insertDataList(l);

	freeDataList(l);
}

void createDataBase()
{
	sqlite3_close(openDb(DBPATH));
	createTable(DBPATH);
}

void dropDataBase()
{
	remove(DBPATH);
}

void displayHelp()
{
	printf("Options de suricastat: \n\n");
	printf("Par default le programme lance les statistiques sur les données importées dans la base\n");
	printf("  -h: affiche ce menu\n");
	printf("  -c: cree la base de données à l'emplacement ../test.db\n");
	printf("  -d: supprime la base de données\n");
	printf("  -f: lit le fichier passé en parametre et affiche les stats\n");
	printf("  -i: importe le passé en parametre dans la base de données\n");
}
