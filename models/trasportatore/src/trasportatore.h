#pragma once
#include <../../utente/src/utente.h>
#include <../../../con2db/pgsql.h>


class Trasportatore: virtual public Utente{
    
    public:
        Trasportatore(char const *nameC, char const *surnameC, char const *emailC, char const *passwordC, char const *purchTypeC) : 
        Utente(nameC, surnameC, emailC, passwordC, purchTypeC){};
    
        void updateStatus(char *idOrdine, Con2DB db1);
};
