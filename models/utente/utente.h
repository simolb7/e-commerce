//
// Created by simolb on 1/29/24.
//

#include "main.h"
using namespace std

typedef enum {costumer,fornitore,trasportatore} Type;

class Utente{
    private:
        string name;
        string surname;
        string email;
        string password;
        string purchType[];
    public:
        Utente(const string &name, const string &surname, const string &email, const string &password, const string[] &purchType)
        : name(name), surname(surname), email(email), password(password), purchType(purchType) {}
};