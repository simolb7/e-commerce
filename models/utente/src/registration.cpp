#include <main.h>

void Utente::registration(Utente utente1, Con2DB db1, char const *ruolo1){
    char const *nomeR  = utente1.getName();
    char const *cognomeR  = utente1.getSurname();
    char const *emailR  = utente1.getEmail();
    char const *passwordR  = utente1.getPassword();
    char const *costumer = "Costumer";
    char const *fornitore = "Fornitore";
    char const *trasportatore = "Trasportatore";
    PGresult *res;
    char sqlcmd[1000];
    int idU;

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
    "INSERT INTO Utente VALUES (DEFAULT, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING", nomeR, cognomeR, emailR, passwordR);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idU FROM Utente WHERE (emailU = \'%s\')", emailR);
    res = db1.ExecSQLtuples(sqlcmd);
    idU = atoi(PQgetvalue(res, 0, PQfnumber(res, "idU")));
    PQclear(res);

    //std::cout << idU;
    if (strcmp(ruolo1, costumer) == 0){
        sprintf(sqlcmd,
        "INSERT INTO Costumer VALUES (\'%d\') ON CONFLICT DO NOTHING", idU);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    }
    
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};
