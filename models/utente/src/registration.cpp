
#include <main.h>

void Utente::registration(){
    char *nome  = utente.getName();
    string cognome  = utente.getSurname();
    string email  = utente.getEmail();
    string password  = utente.getPassword();
    PGresult *res;
    char sqlcmd[1000];

    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
    "INSERT INTO Utente VALUES (%s, %s, %s, %s) ON CONFLICT DO NOTHING", nome, cognome, email, password);
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);
};
