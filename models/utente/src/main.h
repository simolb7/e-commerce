//
// Created by simolb on 1/29/24.
//

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
#include <utente.h>
#include <../../../con2db/pgsql.h>
#include <../../../con2redis/src/con2redis.h>

using namespace std;

/*
#define NAME "Marco"
#define SURNAME "Rossi"
#define EMAIL "marcorossi69@gmail.com"
#define PASSWORD "redigotham"
#define PURCHTYPE "carta di credito"
*/

extern char const *name;
extern char const *surname;
extern char const *email;
extern char const *password;
extern char const *purchType;
extern char const *ruolo;

extern char const *name2;
extern char const *surname2;
extern char const *email2;
extern char const *password2;
extern char const *purchType2;
extern char const *ruolo2;

extern char const *name3;
extern char const *surname3;
extern char const *email3;
extern char const *password3;
extern char const *purchType3;
extern char const *ruolo3;

extern Con2DB db;
extern Utente utente;
extern Utente utente2;
extern Utente utente3;
//extern Utente utente(NAME, SURNAME, EMAIL, PASSWORD, PURCHTYPE);

int micro_sleep(long usec);



#endif //MAIN_H
