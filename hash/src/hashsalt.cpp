#include <hashsalt.h>

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

std::string generateSalt(){
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int saltLength = 16;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.length() - 1);

    std::string salt;
    for (int i = 0; i < saltLength; ++i) {
        salt += characters[dis(gen)];
    }

    return salt;
}

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