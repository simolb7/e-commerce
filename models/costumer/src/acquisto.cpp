#include <main.h>

void Costumer::acquisto(const char * idInv, int idCost, int quantita, Con2DB db1){

   
    int idA;
    int row;
    int qAtt;
    int qAgg;
    PGresult *res;
    char sqlcmd[1000];

    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "INSERT INTO Acquisto VALUES (DEFAULT, 'in preparazione', now(), \'%d\', 3) ON CONFLICT DO NOTHING", idCost);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT quantitaAtt FROM Inventario WHERE (idInv = \'%s\')", idInv);
    res = db1.ExecSQLtuples(sqlcmd);
    qAtt = atoi(PQgetvalue(res, 0, PQfnumber(res, "quantitaAtt")));
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idAcq FROM Acquisto");
    res = db1.ExecSQLtuples(sqlcmd);
    row = PQntuples(res);
    idA = atoi(PQgetvalue(res, row-1, PQfnumber(res, "idAcq")));
    PQclear(res);

    sprintf(sqlcmd,
    "INSERT INTO AcqInv VALUES (\'%s\', \'%d\', \'%d\' )", idInv, idA, quantita);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    qAgg = qAtt - quantita;

    sprintf(sqlcmd,
    "UPDATE Inventario SET quantitaAtt = \'%d\' WHERE (idInv = \'%s\')", qAgg, idInv);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};