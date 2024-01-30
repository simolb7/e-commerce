//
// Created by simolb on 1/29/24.
//

#include "main.h"
using namespace std;

// typedef enum {costumer,fornitore,trasportatore} Type;

class Utente{
    private:
        string name;
        string surname;
        string email;
        string password;
        string purchType[];
    public:
        Utente(const string nameC, const string surnameC, const string emailC, const string passwordC, const string *purchTypeC){
            name = nameC;
            surname = surnameC;
            email = emailC;
            password = passwordC;
            *purchType = *purchTypeC;
        }

        string getName(){
            return name;
        }

        string getSurname(){
            return surname;
        }

        string getEmail(){
            return email;
        }

        string getPassword(){
            return password;
        }
};