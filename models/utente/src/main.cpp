#include <main.h>
#include <fstream>
#include <iostream>
#include <../../../nlohmann/json.hpp>

using namespace std;

//using namespace operazioni;

int main() {
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");
    ifstream i("../../../test_json/utente.json");
    if (!i) {
        cerr << "Errore nell'apertura del file utente.json" << endl;
        return 1; // o gestisci l'errore come preferisci
    }

    nlohmann::json j;
    try {
        i >> j;
    } catch (nlohmann::json::parse_error& e) {
        cerr << "Errore di parsing JSON: " << e.what() << endl;
        return 1; // o gestisci l'errore come preferisci
    }

    for (const auto& user : j) {
        string nome = user["nome"];
        const char *name = nome.c_str(); 

        string cognome = user["cognome"];
        const char *surname = cognome.c_str(); 

        string emailJ = user["email"];
        const char *email = emailJ.c_str(); 

        string passwordJ = user["password"];
        const char *password = passwordJ.c_str(); 

        string purchTypeJ = user["purchType"];
        const char *purchType = purchTypeJ.c_str();

        string ruoloJ = user["ruolo"];
        const char *ruolo = ruoloJ.c_str();

        Utente utente(name, surname, email, password, purchType);
        utente.registration(utente, db, ruolo);
        utente.login(utente, db);
    }

    /*
    char const *name = "Marco";
    char const *surname = "Rossi";
    char const *email = "marcorossi69@gmail.com";
    char const *password = "redigotham";
    char const *purchType = "Carta di credito";
    char const *ruolo = "Fornitore";

    char const *name2 = "Luigi";
    char const *surname2 = "Verdi";
    char const *email2 = "luigiverdi420@gmail.com";
    char const *password2 = "forzapergolettese";
    char const *purchType2 = "Carta di credito";
    char const *ruolo2 = "Costumer";

    char const *name3 = "Stefania";
    char const *surname3 = "Bianchi";
    char const *email3 = "stefaniabianchi88@gmail.com";
    char const *password3 = "grandipalle22";
    char const *purchType3 = "Carta di credito";
    char const *ruolo3 = "Trasportatore";
    */
    
    

    return 0;
};