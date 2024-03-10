#include <main.h>
#include <../../../test/src/test.h>

int main() {
    const char *cost = "Costumer";
    const char *forn = "Fornitore";
    const char *trasp = "Trasportatore";
    PGresult *res;
    char sqlcmd[1000];
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Inserimento dei vari metodi di pagamento all'interno di metpag

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

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT");
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    srand(time(nullptr)); // Inizializza il generatore di numeri casuali

    int numPeople = 50; // Numero di persone da generare

    // Genera i vari utenti
    cout << "Generated "<< numPeople << " users\n";
    for (int i = 0; i < numPeople; ++i) {
        int checkPsw = (rand() %2);
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
            if (checkPsw == 1) {
                password = "1111";
            }
            utente.login(utente, password, db); 
        }
        else if (strcmp(ruolo, forn) == 0){
            const char *pIva = generateRandomPIva().c_str();
            utente.registrationFornitore(utente, password, pIva, db);
            if (checkPsw == 1) {
                password = "1111";
            }
            utente.login(utente, password, db);
        }
        else if (strcmp(ruolo, trasp) == 0){
            const char *azienda = generateRandomAzienda().c_str();
            utente.registrationTrasportatore(utente, password, azienda, db);
            if (checkPsw == 1) {
                password = "1111";
            }
            utente.login(utente, password, db);
        }
        
    }

    return 0;

    
}
