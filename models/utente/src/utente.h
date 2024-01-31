//
// Created by simolb on 1/29/24.
//

#include "main.h"

using namespace std;

// typedef enum {costumer,fornitore,trasportatore} Type;

class Utente{
    private:
        char *nameU;
        const char *surnameU;
        const char *emailU;
        const char *passwordU;
        const char *purchTypeU;
        
    public:
        Utente(char *nameC, const char *surnameC, const char *emailC, const char *passwordC, const char *purchTypeC) : 
        nameU(nameC), surnameU(surnameC), emailU(emailC), passwordU(passwordC), purchTypeU(purchTypeC){}
        

        char* getName(){
            return *nameU;
        }

        string getSurname(){
            return surnameU;
        }

        string getEmail(){
            return emailU;
        }

        string getPassword(){
            return passwordU;
        }

        void registration();
};