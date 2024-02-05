#include <main.h>
#include <fornitore.h>

void Fornitore::addInventario(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1){
    char const *emailF = fornitore1.getEmail();
    char const *BarCodeOg = oggetto1.getBarCodeO();
    int idFor;
    int idOgg;
    PGresult *res;
    char sqlcmd[1000];

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idU FROM Utente WHERE (emailU = \'%s\')", emailF);
    res = db1.ExecSQLtuples(sqlcmd);
    idFor = atoi(PQgetvalue(res, 0, PQfnumber(res, "idU")));
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idO FROM Oggetto WHERE (CBar = \'%s\')", BarCodeOg);
    res = db1.ExecSQLtuples(sqlcmd);
    if (PQresultStatus(res) == PGRES_FATAL_ERROR){
        oggetto1.addOggetto(oggetto1, db1);
    }
    else{
    idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
    PQclear(res);
    }

    sprintf(sqlcmd,
    "INSERT INTO Inventario VALUES (DEFAULT, 99.90, 10, 10, now(), \'%d\', \'%d\')", idFor, idOgg);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};