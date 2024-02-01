//
// Created by simolb on 1/29/24.
//
#include <../../../con2db/pgsql.h>
using namespace std;

// typedef enum {costumer,fornitore,trasportatore} Type;

class Utente{
    private:
        char const *nameU;
        char const *surnameU;
        char const *emailU;
        char const *passwordU;
        char const *purchTypeU;
        
    public:
        Utente(char const *nameC, char const *surnameC, char const *emailC, char const *passwordC, char const *purchTypeC) : 
        nameU(nameC), surnameU(surnameC), emailU(emailC), passwordU(passwordC), purchTypeU(purchTypeC){}
        

        char const * getName(){
            return nameU;
        }

        char const * getSurname(){
            return surnameU;
        }

        char const  * getEmail(){
            return emailU;
        }

        char const * getPassword(){
            return passwordU;
        }

        void registration(Utente utente1, Con2DB db1);

        void login(Utente utente1, Con2DB db1);
};