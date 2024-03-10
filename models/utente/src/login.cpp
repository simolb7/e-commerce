#include <main.h>

// La funzione login gestisce il processo di accesso dell'utente al sistema.
// Prende in input:
// - utente1: un oggetto della classe Utente contenente le informazioni dell'utente che tenta l'accesso.
// - passwordL: la password inserita dall'utente per il login.
// - db1: un oggetto della classe Con2DB utilizzato per l'accesso al database.
void Utente::login(Utente utente1, const char *passwordL, Con2DB db1){
    char const *emailL = utente1.getEmail();
    char const *passwordP;
    const char *salt;
    PGresult *res;
    char sqlcmd[1000];
    char const *controllo;
    char const *t = "t";
    char const *resLog = "info";
    int pid;

    pid = getpid();


    //const char* charHashedPasswordL = passwordL.c_str();

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Controlla se l'email dell'utente è presente nel database
    sprintf(sqlcmd, 
    "SELECT EXISTS (SELECT emailU FROM Utente WHERE (emailU = \'%s\'))", emailL); 
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    if (strcmp(controllo, t) == 0){
        // Inizio transazione
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        // Ottieni la password e il salt dell'utente dal database
        sprintf(sqlcmd,
        "SELECT passwordU, salt FROM Utente WHERE (emailU = \'%s\')", emailL);
        res = db1.ExecSQLtuples(sqlcmd);
        passwordP = PQgetvalue(res, 0, PQfnumber(res, "passwordU"));
        salt = PQgetvalue(res, 0, PQfnumber(res, "salt"));
        PQclear(res);

        // Calcola l'hash della password inserita dall'utente usando il salt ottenuto dal database
        const string saltSTR(salt);
        const string passwordPSTR(passwordP);
        std::string hashedPswdL= hashPassword(passwordL, saltSTR);
        
        // Confronta l'hash calcolato con la password nel database
        if (compareHash(hashedPswdL, passwordPSTR)){
            // Se le password corrispondono, esegui il login con successo e registra l'accesso nel log come "info"
            //resLog = "info";
            sprintf(sqlcmd,
            "INSERT INTO LogLogin VALUES (DEFAULT, now(), 'info', \'%d\', \'%s\') ON CONFLICT DO NOTHING", pid, emailL);
            res = db1.ExecSQLcmd(sqlcmd);
            PQclear(res);
            std::cout << "Login avvenuto con successo - " << emailL << std::endl;
        } else {
            // Se le password non corrispondono, registra il tentativo di accesso nel log come "warn"
            //resLog = "warn";
            sprintf(sqlcmd,
            "INSERT INTO LogLogin VALUES (DEFAULT, now(), 'warn', \'%d\', \'%s\') ON CONFLICT DO NOTHING", pid, emailL);
            res = db1.ExecSQLcmd(sqlcmd);
            PQclear(res);
            std::cout << "Password sbagliata - " << emailL << std::endl;
        }

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else {
        // Inizio transazione
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        // Se l'utente non è presente nel database, registra il tentativo di accesso nel log come "error"
        //resLog = "error";
        sprintf(sqlcmd,
        "INSERT INTO LogLogin VALUES (DEFAULT, now(), 'error', \'%d\', \'%s\') ON CONFLICT DO NOTHING", pid, emailL);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        std::cout << "Email non presente" << std::endl;
    }
};