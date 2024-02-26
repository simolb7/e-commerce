#include <main.h>

// Funzione per generare un nome casuale
string generateRandomFirstName() {
    vector<string> firstNames = {"John", "Jane", "Michael", "Emily", "David", "Sarah"};
    return firstNames[rand() % firstNames.size()];
}

// Funzione per generare un cognome casuale
string generateRandomLastName() {
    vector<string> lastNames = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia"};
    return lastNames[rand() % lastNames.size()];
}

string generateEmail(const char* nome, const char* cognome) { 
    string nomes = nome;
    transform(nomes.begin(), nomes.end(), nomes.begin(), ::tolower);
    string surnames = cognome;
    transform(surnames.begin(), surnames.end(), surnames.begin(), ::tolower);
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
Utente generateRandomUser() {

    const char* nome = generateRandomFirstName().c_str();
    const char* cognome = generateRandomLastName().c_str();
    const char* email = generateEmail(nome, cognome).c_str();
    const char* password = "0000";
    const char* purchType = generateRandomPurchType().c_str();
    Utente utente(nome, cognome, email, password, purchType);

    return utente;
}

int main() {
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    srand(time(nullptr)); // Inizializza il generatore di numeri casuali

    int numPeople = 5; // Numero di persone da generare

    cout << "Generated People:\n";
    for (int i = 0; i < numPeople; ++i) {
        Utente utente = generateRandomUser();
        printf("Utente %d: %s, %s, email: %s, password: %s\n", i + 1, utente.getName(), utente.getSurname(), utente.getEmail(), utente.getPassword());
        const char *ruolo = generateRandomType().c_str();
        utente.registration(utente, db, ruolo);
    }

    return 0;
}
