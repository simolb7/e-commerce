#include <main.h>
#include <../../../test/src/test.h>

// Funzione per generare una persona casuale

int main() {
    const char *cost = "Costumer";
    const char *forn = "Fornitore";
    const char *trasp = "Trasportatore";
    PGresult *res;
    char sqlcmd[1000];
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
    "INSERT INTO metpag VALUES (DEFAULT, 'PayPal') ON CONFLICT DO NOTHING"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
    "INSERT INTO metpag VALUES (DEFAULT, 'Carta di credito') ON CONFLICT DO NOTHING"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
    "INSERT INTO metpag VALUES (DEFAULT, 'Bonifico bancario') ON CONFLICT DO NOTHING"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 

    srand(time(nullptr)); // Inizializza il generatore di numeri casuali

    int numPeople = 20; // Numero di persone da generare

    cout << "Generated "<< numPeople << " users\n";
    for (int i = 0; i < numPeople; ++i) {
        const char *nome = generateRandomFirstName().c_str();
        const char *cognome = generateRandomLastName().c_str();
        string nomes(nome);
        transform(nomes.begin(), nomes.end(), nomes.begin(), ::tolower);
        string cognomes(cognome);
        transform(cognomes.begin(), cognomes.end(), cognomes.begin(), ::tolower);
        int num = rand() %100;
        string nums = to_string(num);
        string emails = nomes+"."+cognomes+nums+"@gmail.com";
        const char *password = "0000";
        const char *purchType = generateRandomPurchType().c_str();
        const char *email = emails.c_str(); 
        Utente utente(nome, cognome, email);
        const char *ruolo = generateRandomType().c_str();
        int purch = (rand() %3)+1;
        if (strcmp(ruolo, cost) == 0){
            utente.registrationCostumer(utente, db, password, purch);
            utente.login(utente, password, db); 
        }
        else if (strcmp(ruolo, forn) == 0){
            const char *pIva = generateRandomPIva().c_str();
            utente.registrationFornitore(utente, pIva, password, db);
            utente.login(utente, password, db);
        }
        else if (strcmp(ruolo, trasp) == 0){
            const char *azienda = generateRandomAzienda().c_str();
            utente.registrationTrasportatore(utente, password, azienda, db);
            utente.login(utente, password, db);
        }
        
    }

    return 0;

    
}
