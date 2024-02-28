#include <main.h>

std::string hashPassword(const std::string& password, const std::string& salt) {
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

// Funzione per generare un salt casuale
std::string generateSalt() {
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

void Utente::registration(Utente utente1, Con2DB db1, char const *ruolo1){
    char const *nomeR  = utente1.getName();
    char const *cognomeR  = utente1.getSurname();
    char const *emailR  = utente1.getEmail();
    const string passwordR(utente1.getPassword());
    char const *costumer = "Costumer";
    char const *fornitore = "Fornitore";
    char const *trasportatore = "Trasportatore";
    char const *pIva = "12345678901";
    PGresult *res;
    char sqlcmd[1000];
    int idU;

    std::string salt = generateSalt();
    std::string hashedPassword = hashPassword(passwordR, salt);

    const char* charSalt = salt.c_str();
    const char* charHashedPassword = hashedPassword.c_str();

    //std::cout << "Generated salt: " <<charSalt << std::endl;
    //std::cout << "Hashed password: " << charHashedPassword << std::endl;

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
    "INSERT INTO Utente VALUES (DEFAULT, \'%s\', \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING", nomeR, cognomeR, emailR, charHashedPassword, charSalt);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idU FROM Utente WHERE (emailU = \'%s\')", emailR);
    res = db1.ExecSQLtuples(sqlcmd);
    idU = atoi(PQgetvalue(res, 0, PQfnumber(res, "idU")));
    PQclear(res);

    if (strcmp(ruolo1, costumer) == 0){
        sprintf(sqlcmd,
        "INSERT INTO Costumer VALUES (\'%d\') ON CONFLICT DO NOTHING", idU);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    }
    else if (strcmp(ruolo1, fornitore) == 0){
        sprintf(sqlcmd,
        "INSERT INTO Fornitore VALUES (\'%d\', \'%s\') ON CONFLICT DO NOTHING", idU, pIva);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    }
    else if (strcmp(ruolo1, trasportatore) == 0){
        sprintf(sqlcmd,
        "INSERT INTO Trasportatore VALUES (\'%d\', 'Bartolini') ON CONFLICT DO NOTHING", idU);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    }
    
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};
