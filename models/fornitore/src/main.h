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
#include <fornitore.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

extern char const *nomeOgg;
extern char const *descrizioneOgg;
extern char const *barCodeOgg;
extern char const *categoriaOgg;

extern char const *name;
extern char const *surname;
extern char const *email;
extern char const *password;
extern char const *purchType;
extern char const *ruolo;

extern Con2DB db;
#endif //MAIN_H