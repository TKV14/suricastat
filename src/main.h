#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "file.h"
#include "db.h"
#include "gestionStruct.h"
#include "stats.h"

void launchStats();
void launchStatsFile(char *log);
void launchImport(char *log);
void createDataBase();
void dropDataBase();
void displayHelp();
