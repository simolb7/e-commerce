#include <main.h>

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

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
    "SELECT EXISTS (SELECT emailU FROM Utente WHERE (emailU = \'%s\'))", emailL); 
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
        "SELECT passwordU, salt FROM Utente WHERE (emailU = \'%s\')", emailL);
        res = db1.ExecSQLtuples(sqlcmd);
        passwordP = PQgetvalue(res, 0, PQfnumber(res, "passwordU"));
        salt = PQgetvalue(res, 0, PQfnumber(res, "salt"));
        PQclear(res);

        const string saltSTR(salt);
        const string passwordPSTR(passwordP);
        std::string hashedPswdL= hashPassword(passwordL, saltSTR);
        
        if (compareHash(hashedPswdL, passwordPSTR)){
            //resLog = "info";
            sprintf(sqlcmd,
            "INSERT INTO LogLogin VALUES (DEFAULT, now(), 'info', \'%d\', \'%s\') ON CONFLICT DO NOTHING", pid, emailL);
            res = db1.ExecSQLcmd(sqlcmd);
            PQclear(res);
            std::cout << "Login avvenuto con successo" << std::endl;
        } else {
            //resLog = "warn";
            sprintf(sqlcmd,
            "INSERT INTO LogLogin VALUES (DEFAULT, now(), 'warn', \'%d\', \'%s\') ON CONFLICT DO NOTHING", pid, emailL);
            res = db1.ExecSQLcmd(sqlcmd);
            PQclear(res);
            std::cout << "Password sbagliata" << std::endl;
        }

        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else {
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        //resLog = "error";

        sprintf(sqlcmd,
        "INSERT INTO LogLogin VALUES (DEFAULT, now(), 'error', \'%d\', \'%s\') ON CONFLICT DO NOTHING", pid, emailL);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        std::cout << "Email non presente" << std::endl;
    }
};