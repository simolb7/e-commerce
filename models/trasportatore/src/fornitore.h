#pragma once
#include <../../utente/src/utente.h>
#include <../../../con2db/pgsql.h>
#include <oggetto.h> 

class Fornitore: virtual public Utente{
    
    public:
        Fornitore(char const *nameC, char const *surnameC, char const *emailC, char const *passwordC, char const *purchTypeC) : 
        Utente(nameC, surnameC, emailC, passwordC, purchTypeC){};
          
        void addInventario(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1);

        void addQuantity(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1, int aggiunta);
};
