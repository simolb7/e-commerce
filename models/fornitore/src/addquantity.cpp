#pragma once
#include <main.h>
#include <fornitore.h>

void Fornitore::addQuantity(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1, int aggiunta){
    char const *emailF = fornitore1.getEmail();
    char const *BarCodeOg = oggetto1.getBarCodeO();
    int idFor;
    int idOgg;
    int qAtt;
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
    "SELECT idO FROM Oggetto WHERE (CBar = \'%s\')", BarCodeOg);
    res = db1.ExecSQLtuples(sqlcmd);
    idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT quantitaatt FROM Inventario WHERE (Fornitore = \'%d\' AND Oggetto = \'%d\')", idFor, idOgg);
    res = db1.ExecSQLtuples(sqlcmd);
    qAtt = atoi(PQgetvalue(res, 0, PQfnumber(res, "quantitaatt")));
    PQclear(res);

    qAtt += aggiunta;
    sprintf(sqlcmd,
    "UPDATE Inventario SET quantitaatt = \'%d\' WHERE (Fornitore = \'%d\' AND Oggetto = \'%d\')", qAtt, idFor, idOgg);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};