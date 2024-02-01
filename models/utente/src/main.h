//
// Created by simolb on 1/29/24.
//

#ifndef MAIN_H
#define MAIN_H

//#include <con2redis.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <utente.h>
#include <../../../con2db/pgsql.h>

#define READ_STREAM "stream2"
#define WRITE_STREAM "stream1"

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


extern Con2DB db;
extern Utente utente;
//extern Utente utente(NAME, SURNAME, EMAIL, PASSWORD, PURCHTYPE);


#endif //MAIN_H
