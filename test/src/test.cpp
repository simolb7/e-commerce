#include <test.h>

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

string generateRandomObjName() {
    vector<string> objNames = {"Mouse", 
        "Monitor", 
        "Tastiera", 
        "Cuffie", 
        "Alimentatore", 
        "Televisore", 
        "Scheda audio",
        "Scheda di rete",
        "Tastiera"
        /*
        "Stampante",
        "Scanner",
        "Router",
        "Switch",
        "Hub",
        "Webcam",
        "Microfono",
        "Cuffie",
        "Altoparlanti",
        "Penna USB",
        "PC case",
        "CPU",
        "Scheda madre",
        "Memoria RAM",
        "Hard Disk",
        "GPU"
        */
       };
    return objNames[rand() % objNames.size()];
}

string generateRandomBarCode() {
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 9);

    std::string number;
    for (int i = 0; i < 13; ++i) {
        number += std::to_string(distribution(generator));
    }

    return number;

}

float generatePrice(){
    int num = rand() %300;
    float numf = static_cast<float>(num) + 0.99f;
    return numf;
}

