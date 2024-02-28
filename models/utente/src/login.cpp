#include <main.h>

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
    std::string hashedPswdL= hashPassword(passwordL, saltSTR);
    
    if (compareHash(hashedPswdL, passwordPSTR)){
        std::cout << "Login avvenuto con successo" << std::endl;
    } else {
        std::cout << "Password sbagliata" << std::endl;
    }

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};