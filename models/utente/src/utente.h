#pragma once
#include <../../../con2db/pgsql.h>
using namespace std;


class Utente{
    protected:
        char const *nameU;
        char const *surnameU;
        char const *emailU;
        
    public:
        Utente(char const *nameC, char const *surnameC, char const *emailC) : 
        nameU(nameC), surnameU(surnameC), emailU(emailC){}
        

        char const * getName(){
            return nameU;
        }

        char const * getSurname(){
            return surnameU;
        }

        char const  * getEmail(){
            return emailU;
        }

        void registrationCostumer(Utente utente1, Con2DB db1, const char *password, int purch);

        void registrationFornitore(Utente utente1, const char *password, const char *pIva, Con2DB db1);

        void registrationTrasportatore(Utente utente1, const char *password, const char *azienda, Con2DB db1);

        void login(Utente utente1, const char *password, Con2DB db1);
};