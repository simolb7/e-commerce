#pragma once
#include <../../utente/src/utente.h>
#include <../../../con2db/pgsql.h>
#include <iostream>

class Costumer: public Utente{
    
    public:
        Costumer(char const *nameC, char const *surnameC, char const *emailC, char const *passwordC, char const *purchTypeC) : 
        Utente(nameC, surnameC, emailC, passwordC, purchTypeC){};

        void acquisto(const char * idInv, int idCost, int quantita, Con2DB db1);

        void ricerca(char const * nomeOg, int quantita, std::string result[30][4], Con2DB db1);
};