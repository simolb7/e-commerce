#include <main.h>

void Utente::login(Utente utente1, Con2DB db1){
    char const *emailL = utente1.getEmail();
    char const *passwordL = utente1.getPassword();
    char const *passwordP;
    PGresult *res;
    char sqlcmd[1000];

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT passwordU FROM Utente WHERE (emailU = \'%s\')", emailL);
    res = db1.ExecSQLtuples(sqlcmd);
    passwordP = PQgetvalue(res, 0, PQfnumber(res, "passwordU"));
    PQclear(res);

    if (strcmp(passwordL, passwordP) == 0){
        cout << "Login avvenuto con successo" << endl;
    } else {
        cout << "Paaword non corretta" << endl;
    }

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};