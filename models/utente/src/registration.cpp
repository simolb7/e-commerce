
#include <main.h>

void Utente::registration(){
    char const *nomeR  = utente.getName();
    char const *cognomeR  = utente.getSurname();
    char const *emailR  = utente.getEmail();
    char const *passwordR  = utente.getPassword();
    PGresult *res;
    char sqlcmd[1000];

    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
    "INSERT INTO Utente VALUES (%s, %s, %s, %s) ON CONFLICT DO NOTHING", nomeR, cognomeR, emailR, passwordR);
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);
};
