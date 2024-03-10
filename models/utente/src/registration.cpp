#include <main.h>

#include <../../../hash/src/hashsalt.h>

// La funzione registrationCostumer gestisce il processo di registrazione di un cliente nel sistema.
// Prende in input:
// - utente1: un oggetto della classe Utente contenente le informazioni del cliente da registrare.
// - db1: un oggetto della classe Con2DB utilizzato per l'accesso al database.
// - passwordR: la password scelta dal cliente per la registrazione.
// - purch: il metodo di pagamento rappresentato da un id tramite intero.
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

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Controlla se l'email dell'utente è presente nel database
    sprintf(sqlcmd, 
    "SELECT EXISTS (SELECT emailU FROM Utente WHERE (emailU = \'%s\'))", emailR); 
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res); 

    // Se l'email è già presente nel database, registra un log di errore
    if (strcmp(controllo, t) == 0){
        // Inizio transazione
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO LogReg VALUES (DEFAULT, now(), 'error', \'%d\', \'%s\', 'customer') ON CONFLICT DO NOTHING", pid, emailR);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    // Se non è presente nel database, registra l'untente come customer al suo interno
    } else {
        // Inizio transazione
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

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res); 
    } 
};

// La funzione registrationFornitore gestisce il processo di registrazione di un fornitore nel sistema.
// Prende in input:
// - utente1: un oggetto della classe Utente contenente le informazioni del fornitore da registrare.
// - passwordR: la password scelta dal fornitore per la registrazione.
// - pIva: il codice di partita IVA del fornitore.
// - db1: un oggetto della classe Con2DB utilizzato per l'accesso al database.
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

    // Genera un sale e calcola l'hash della password
    std::string salt = generateSalt();
    std::string hashedPassword = hashPassword(passwordR, salt);

    const char* charSalt = salt.c_str();
    const char* charHashedPassword = hashedPassword.c_str();

    //std::cout << "Generated salt: " <<charSalt << std::endl;
    //std::cout << "Hashed password: " << charHashedPassword << std::endl;

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Controlla se l'email dell'utente è presente nel database
    sprintf(sqlcmd, 
    "SELECT EXISTS (SELECT emailU FROM Utente WHERE (emailU = \'%s\'))", emailR); 
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Se l'email è già presente nel database, registra un log di errore
    if (strcmp(controllo, t) == 0){
        // Inizio transazione
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO LogReg VALUES (DEFAULT, now(), 'error', \'%d\', \'%s\', 'fornitore') ON CONFLICT DO NOTHING", pid, emailR);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    // Se non è presente nel database, registra l'untente come fornitore al suo interno
    } else {
        // Inizio transazione
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

        // Chiude la transazione
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

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Controlla se l'email dell'utente è presente nel database
    sprintf(sqlcmd, 
    "SELECT EXISTS (SELECT emailU FROM Utente WHERE (emailU = \'%s\'))", emailR); 
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Se l'email è già presente nel database, registra un log di errore
    if (strcmp(controllo, t) == 0){
        // Inizio transazione
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO LogReg VALUES (DEFAULT, now(), 'error', \'%d\', \'%s\', 'trasportatore') ON CONFLICT DO NOTHING", pid, emailR);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    // Se non è presente nel database, registra l'untente come trasportatore al suo interno
    } else {
        // Inizio transazione
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

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);  
    } 
}