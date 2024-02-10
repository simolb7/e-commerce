#include <main.h>

class Costumer: public Utente{
    
    public:
        Costumer(char const *nameC, char const *surnameC, char const *emailC, char const *passwordC, char const *purchTypeC) : 
        Utente(nameC, surnameC, emailC, passwordC, purchTypeC){};

        void acquisto(char * idInv, Costumer costumer1, int quantita, Con2DB db1);

        void ricerca(char const * nomeOg, int quantita, char * result[][4], Con2DB db1);
};