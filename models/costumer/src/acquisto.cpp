#include <main.h>

void Costumer::acquisto(char * idInv, Costumer costumer1, int quantita, Con2DB db1){
    char const *emailCost = costumer1.getEmail();
    int idCost;
    int idA;
    int row;
    PGresult *res;
    char sqlcmd[1000];

    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd,
    "SELECT idU FROM Utente WHERE (emailU = \'%s\')", emailCost);
    res = db1.ExecSQLtuples(sqlcmd);
    idCost = atoi(PQgetvalue(res, 0, PQfnumber(res, "idU")));
    PQclear(res);

    sprintf(sqlcmd,
    "INSERT INTO Acquisto VALUES (DEFAULT, 'in preparazione', now(), \'%d\', 3)", idCost);
    res = db1.ExecSQLcmd(sqlcmd);
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

    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};