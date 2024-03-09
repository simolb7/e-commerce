#pragma once
#include <../../utente/src/utente.h>
#include <../../../con2db/pgsql.h>


class Trasportatore: virtual public Utente{
    
    public:
        Trasportatore(char const *nameC, char const *surnameC, char const *emailC) : 
        Utente(nameC, surnameC, emailC){};
    
        void updateStatus(int idOrdine, Con2DB db1);

        char *getStatus(int idOrdine, Con2DB db1);

        void getOrders(int idT, Con2DB db1, int orders[]);

        
};
