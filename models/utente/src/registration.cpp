#include <main.h>

void Utente::registrationCostumer(Utente utente1, Con2DB db1){
    char const *nomeR  = utente1.getName();
    char const *cognomeR  = utente1.getSurname();
    char const *emailR  = utente1.getEmail();
    const string passwordR(utente1.getPassword());
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

    sprintf(sqlcmd,
    "INSERT INTO Costumer VALUES (\'%d\') ON CONFLICT DO NOTHING", idU);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};


void Utente::registrationFornitore(Utente utente1, const char *pIva, Con2DB db1){
    char const *nomeR  = utente1.getName();
    char const *cognomeR  = utente1.getSurname();
    char const *emailR  = utente1.getEmail();
    const string passwordR(utente1.getPassword());
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

    sprintf(sqlcmd,
    "INSERT INTO Fornitore VALUES (\'%d\', \'%s\') ON CONFLICT DO NOTHING", idU, pIva);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};


void Utente::registrationTrasportatore(Utente utente1, const char *azienda, Con2DB db1){
    char const *nomeR  = utente1.getName();
    char const *cognomeR  = utente1.getSurname();
    char const *emailR  = utente1.getEmail();
    const string passwordR(utente1.getPassword());
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

    sprintf(sqlcmd,
    "INSERT INTO Trasportatore VALUES (\'%d\', \'%s\') ON CONFLICT DO NOTHING", idU, azienda);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
}