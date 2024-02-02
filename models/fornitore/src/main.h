#ifndef MAIN_H
#define MAIN_H

//#include <con2redis.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <../../utente/src/utente.h>
#include <../../../con2db/pgsql.h>

#define READ_STREAM "stream2"
#define WRITE_STREAM "stream1"

using namespace std;

extern Con2DB db;
#endif //MAIN_H