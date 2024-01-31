//
// Created by simolb on 1/29/24.
//

#ifndef MAIN_H
#define MAIN_H

//#include <con2redis.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <time.h>
#include <math.h>
//#include <operazioni.h>
#include <utente.h>
#include <../../../con2db/pgsql.h>

#define READ_STREAM "stream2"
#define WRITE_STREAM "stream1"

using namespace std;

/*#define NAME  "Marco"
#define SURNAME string "Rossi"
#define EMAIL string "marcorossi69@gmail.com"
#define PASSWORD string "redigotham"
#define PURCHTYPE ["Paypal", "Mastercard", "Visa", "BitCoin", "ETH"]*/

string name = "Marco";
string surname = "Rossi";
string email = "marcorossi69@gmail.com";
string password = "redigotham";
string purchType[5] = {"Paypal", "Mastercard", "Visa", "BitCoin", "ETH"};

Con2DB db("localost", "5432", "userdb", "47002", "ecommercedb");
Utente utente(name, surname, email, password, purchType);


#endif //MAIN_H
