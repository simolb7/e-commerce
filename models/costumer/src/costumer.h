#pragma once
#include <../../utente/src/utente.h>
#include <../../../con2db/pgsql.h>
#include <iostream>

class Costumer: public Utente{
    
    public:
        Costumer(char const *nameC, char const *surnameC, char const *emailC) : 
        Utente(nameC, surnameC, emailC){};

        void acquisto(const char * idInv, int idCost, int idTrasp, int quantita, Con2DB db1);

        void ricerca(char const * nomeOg, int quantita, std::string result[30][4], Con2DB db1);
};