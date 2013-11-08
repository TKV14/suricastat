#include "main.h"

int main(void)
{
//	float time;
//	clock_t t1, t2;
	dataList *l = NULL;

//	t1 = clock();
//	openDb(DBPATH);
//	createTable(DBPATH);
//	importFile("../stats.log");

	readDataBase(&l);
	stats(l);

//	t2 = clock();

//	time = (float)(t2-t1)/CLOCKS_PER_SEC;
//	printf("temps = %f\n", time);

	return 0;
}
