#include <main.h>

#include <../../../hash/src/hashsalt.h>

void Utente::registrationCostumer(Utente utente1, Con2DB db1, const char *passwordR, int purch){
    char const *nomeR  = utente1.getName();
    char const *cognomeR  = utente1.getSurname();
    char const *emailR  = utente1.getEmail();
    PGresult *res;
    char sqlcmd[1000];
    int idU;
    int pid;
    const char *controllo;
    const char *t = "t";

    pid = getpid();

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
    "SELECT EXISTS (SELECT emailU FROM Utente WHERE (emailU = \'%s\'))", emailR); 
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res); 

    if (strcmp(controllo, t) == 0){
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO LogReg VALUES (DEFAULT, now(), 'error', \'%d\', \'%s\', 'customer') ON CONFLICT DO NOTHING", pid, emailR);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else {
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

        sprintf(sqlcmd,
        "INSERT INTO MPUte VALUES (\'%d\', \'%d\') ON CONFLICT DO NOTHING", idU, purch);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO LogReg VALUES (DEFAULT, now(), 'info', \'%d\', \'%s\', 'customer') ON CONFLICT DO NOTHING", pid, emailR);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res); 
    } 
};


void Utente::registrationFornitore(Utente utente1, const char *passwordR, const char *pIva, Con2DB db1){
    char const *nomeR  = utente1.getName();
    char const *cognomeR  = utente1.getSurname();
    char const *emailR  = utente1.getEmail();
    PGresult *res;
    char sqlcmd[1000];
    int idU;
    int pid;
    const char *controllo;
    const char *t = "t";

    pid = getpid();

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
    "SELECT EXISTS (SELECT emailU FROM Utente WHERE (emailU = \'%s\'))", emailR); 
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    if (strcmp(controllo, t) == 0){
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO LogReg VALUES (DEFAULT, now(), 'error', \'%d\', \'%s\', 'fornitore') ON CONFLICT DO NOTHING", pid, emailR);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else {
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

        sprintf(sqlcmd,
        "INSERT INTO LogReg VALUES (DEFAULT, now(), 'info', \'%d\', \'%s\', 'fornitore') ON CONFLICT DO NOTHING", pid, emailR);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res); 
    }
};


void Utente::registrationTrasportatore(Utente utente1, const char *passwordR, const char *azienda, Con2DB db1){
    char const *nomeR  = utente1.getName();
    char const *cognomeR  = utente1.getSurname();
    char const *emailR  = utente1.getEmail();
    PGresult *res;
    char sqlcmd[1000];
    int idU;
    int pid;
    const char *controllo;
    const char *t = "t";

    pid = getpid();

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
    "SELECT EXISTS (SELECT emailU FROM Utente WHERE (emailU = \'%s\'))", emailR); 
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    if (strcmp(controllo, t) == 0){
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO LogReg VALUES (DEFAULT, now(), 'error', \'%d\', \'%s\', 'trasportatore') ON CONFLICT DO NOTHING", pid, emailR);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else {
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

        sprintf(sqlcmd,
        "INSERT INTO LogReg VALUES (DEFAULT, now(), 'info', \'%d\', \'%s\', 'trasportatore') ON CONFLICT DO NOTHING", pid, emailR);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);  
    } 
}