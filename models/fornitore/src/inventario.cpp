#include <main.h>
#include <fornitore.h>

void Fornitore::addInventario(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1, float prezzo, int quantity){
    char const *emailF = fornitore1.getEmail();
    char const *BarCodeOg = oggetto1.getBarCodeO();
    int idFor;
    int idOgg;
    char const *controllo;
    char const *t = "t";
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
    "SELECT EXISTS (SELECT idO FROM Oggetto WHERE (CBar = \'%s\'))", BarCodeOg);
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    if (strcmp(controllo, t) == 0){
        sprintf(sqlcmd,
        "SELECT idO FROM Oggetto WHERE (CBar = \'%s\')", BarCodeOg);
        res = db1.ExecSQLtuples(sqlcmd);
        idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO Inventario VALUES (DEFAULT, \'%f\', \'%d\', \'%d\', now(), \'%d\', \'%d\') ON CONFLICT DO NOTHING", prezzo, quantity, quantity, idFor, idOgg);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else {
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        oggetto1.addOggetto(oggetto1, db1);

        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd,
        "SELECT idO FROM Oggetto WHERE (CBar = \'%s\')", BarCodeOg);
        res = db1.ExecSQLtuples(sqlcmd);
        idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO Inventario VALUES (DEFAULT, \'%f\', \'%d\', \'%d\', now(), \'%d\', \'%d\') ON CONFLICT DO NOTHING", prezzo, quantity, quantity, idFor, idOgg);       res = db1.ExecSQLcmd(sqlcmd);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    }
};