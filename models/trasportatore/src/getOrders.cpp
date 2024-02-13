#include <main.h>

void Trasportatore::getOrders(Trasportatore trasportatore, Con2DB db1, int orders[]){

    PGresult *res;
    char sqlcmd[1000];
    const char *emailT = trasportatore.getEmail();
    int idT;
    int row;

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
            "SELECT idU FROM Utente WHERE (emailU = \'%s\')", emailT);
    res = db1.ExecSQLtuples(sqlcmd);
    idT = atoi(PQgetvalue(res, 0, PQfnumber(res, "idU")));
    PQclear(res);

    sprintf(sqlcmd, 
            "SELECT idAcq FROM Acquisto WHERE (trasportatore = \'%d\')", idT);
    res = db1.ExecSQLtuples(sqlcmd);
    row = PQntuples(res);
    for(int i = 0; i < row; i++){
        int val = atoi(PQgetvalue(res, i, PQfnumber(res, "idAcq")));
        orders[i] = val;
    }
    PQclear(res);
    
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

};
