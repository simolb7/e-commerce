#ifndef MAIN_H
#define MAIN_H

#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <../../../con2db/pgsql.h>
#include <../../../con2redis/src/con2redis.h>
#include <trasportatore.h>


using namespace std;

extern char const *name;
extern char const *surname;
extern char const *email;
extern char const *password;
extern char const *purchType;
extern char const *ruolo;

extern Con2DB db;
#endif //MAIN_H