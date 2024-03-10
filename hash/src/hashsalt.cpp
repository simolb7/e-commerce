#include <hashsalt.h>

// La funzione hashPassword calcola l'hash di una password utilizzando l'algoritmo SHA-256 e un salt.
// Prende in input:
// - password: una stringa rappresentante la password.
// - salt: una stringa rappresentante il salt da aggiungere alla password.
std::string hashPassword(const std::string& password, const std::string& salt){
    // Concateniamo la password e il salt
    std::string combinedString = password + salt;

    // Buffer per contenere l'hash
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Calcoliamo l'hash utilizzando SHA-256
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, combinedString.c_str(), combinedString.length());
    SHA256_Final(hash, &sha256);

    // Convertiamo l'hash binario in una stringa esadecimale
    std::string hashedString;
    char hex[3];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hex, "%02x", hash[i]);
        hashedString += hex;
    }

    return hashedString;
}

// La funzione generateSalt genera un salt casuale di lunghezza specificata.
// Restituisce il salt generato.
std::string generateSalt(){
    // Definiamo i caratteri utilizzati per generare il salt
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int saltLength = 16;

    // Inizializziamo il generatore di numeri casuali
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.length() - 1);

    // Generiamo il salt
    std::string salt;
    for (int i = 0; i < saltLength; ++i) {
        salt += characters[dis(gen)];
    }

    return salt;
}

// La funzione compareHash confronta due hash e restituisce true se sono identici, altrimenti false.
// Prende in input due stringhe rappresentanti gli hash da confrontare.
bool compareHash(const std::string& hash1, const std::string& hash2){
    // Confrontiamo i caratteri uno per uno
    for (size_t i = 0; i < hash1.length(); ++i) {
        if (hash1[i] != hash2[i]) {
            // Se troviamo un carattere diverso, gli hash sono diversi
            return false;
        }
    }
    // Se non abbiamo trovato differenze, gli hash sono uguali
    return true;
}