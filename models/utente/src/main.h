//
// Created by simolb on 1/29/24.
//

#ifndef MAIN_H
#define MAIN_H

//#include <con2redis.h>
#pragma once
//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <utente.h>
#include <../../../con2db/pgsql.h>
#include <../../../con2redis/src/con2redis.h>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <bits/stdc++.h>
#include <../../../hash/src/hashsalt.h>


using namespace std;

extern char const *name;
extern char const *surname;
extern char const *email;
extern char const *password;
extern char const *purchType;
extern char const *ruolo;

extern Con2DB db;
extern Utente utente;

int micro_sleep(long usec);



#endif //MAIN_H
