#include <main.h>

std::string hashPasswordLogin(const std::string& password, const std::string& salt) {
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

bool compareHash(const std::string& hash1, const std::string& hash2) {
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

void Utente::login(Utente utente1, Con2DB db1){
    char const *emailL = utente1.getEmail();
    const string passwordL(utente1.getPassword());
    char const *passwordP;
    const char *salt;
    PGresult *res;
    char sqlcmd[1000];


    //const char* charHashedPasswordL = passwordL.c_str();

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT passwordU, salt FROM Utente WHERE (emailU = \'%s\')", emailL);
    res = db1.ExecSQLtuples(sqlcmd);
    passwordP = PQgetvalue(res, 0, PQfnumber(res, "passwordU"));
    salt = PQgetvalue(res, 0, PQfnumber(res, "salt"));
    PQclear(res);

    const string saltSTR(salt);
    const string passwordPSTR(passwordP);
    std::string hashedPswdL= hashPasswordLogin(passwordL, saltSTR);
    
    if (compareHash(hashedPswdL, passwordPSTR)){
        std::cout << "Login avvenuto con successo" << std::endl;
    } else {
        std::cout << "Password sbagliata" << std::endl;
    }

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};