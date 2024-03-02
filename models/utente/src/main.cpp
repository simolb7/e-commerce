#include <main.h>

// Funzione per generare un nome casuale
string generateRandomFirstName() {
    vector<string> firstNames = {"Mario", "Luigi", "Giovanni", "Paolo", "Giulia", "Laura", "Francesca", "Alessandra", "Roberto", "Andrea"};
    return firstNames[rand() % firstNames.size()];
}

// Funzione per generare un cognome casuale
string generateRandomLastName() {
    vector<string> lastNames = {"Rossi", "Bianchi", "Verdi", "Ferrari", "Russo", "Romano", "Gallo", "Conti", "Esposito", "Bruno"};
    return lastNames[rand() % lastNames.size()];
}

string generateEmail(const char *nome, const char *cognome) { 
    string nomes = nome;
    string surnames = cognome;
    int num = rand() %100;
    string nums = to_string(num);
    string email = nomes + surnames + nums + "@gmail.com";
    return email;
}
 
string generateRandomType() {
    vector<string> lastNames = {"Costumer", "Fornitore", "Trasportatore"};
    return lastNames[rand() % lastNames.size()];
}

string generateRandomPurchType() {
    vector<string> lastNames = {"Paypal", "Carta di credito"};
    return lastNames[rand() % lastNames.size()];
}

string generateRandomPIva() {
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 9);
    std::string number;

    for (int i = 0; i < 11; ++i) {
        number += std::to_string(distribution(generator));
    }

    return number;
}


string generateRandomAzienda() {
    vector<string> lastNames = {"Bartolini", "GLS", "Fedex", "UPS", "Poste Italiane", "TNT"};
    return lastNames[rand() % lastNames.size()];
}


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

    cout << "Generated People:\n";
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
        Utente utente(nome, cognome, email, password, purchType);
        //printf("Utente %d: %s, %s, email: %s, password: %s\n", i + 1, utente.getName(), utente.getSurname(), utente.getEmail(), utente.getPassword());
        const char *ruolo = generateRandomType().c_str();
        int purch = (rand() %3)+1;
        if (strcmp(ruolo, cost) == 0){
            utente.registrationCostumer(utente, db, purch);
            utente.login(utente, db); 
        }
        else if (strcmp(ruolo, forn) == 0){
            const char *pIva = generateRandomPIva().c_str();
            utente.registrationFornitore(utente, pIva, db);
            utente.login(utente, db);
        }
        else if (strcmp(ruolo, trasp) == 0){
            const char *azienda = generateRandomAzienda().c_str();
            utente.registrationTrasportatore(utente, azienda, db);
            utente.login(utente, db);
        }
        
    }

    return 0;

    
}
