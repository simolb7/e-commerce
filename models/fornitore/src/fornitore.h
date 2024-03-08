#pragma once
#include <../../utente/src/utente.h>
#include <../../../con2db/pgsql.h>
#include <oggetto.h> 

class Fornitore: public Utente{
    
    public:
        Fornitore(char const *nameC, char const *surnameC, char const *emailC) : 
        Utente(nameC, surnameC, emailC){};
          
        void addInventario(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1, float prezzo, int quantity);

        void addQuantity(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1, int aggiunta);
};
