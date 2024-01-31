//
// Created by simolb on 1/29/24.
//

#include "main.h"

using namespace std;

// typedef enum {costumer,fornitore,trasportatore} Type;

class Utente{
    private:
        string nameU;
        string surnameU;
        string emailU;
        string passwordU;
        string purchTypeU[5];
        
    public:
        Utente(const string nameC, const string surnameC, const string emailC, const string passwordC, const string *purchTypeC) : 
        nameU(nameC), surnameU(surnameC), emailU(emailC), passwordU(passwordC)
        {
            *purchTypeU = *purchTypeC;
        }

        string getName(){
            return nameU;
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