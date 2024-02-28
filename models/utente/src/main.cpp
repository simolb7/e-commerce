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

// Funzione per generare una persona casuale

int main() {
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

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
        utente.registration(utente, db, ruolo);
        utente.login(utente, db);
    }

    return 0;

    
}
