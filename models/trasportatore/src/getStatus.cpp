#include <main.h>
#include "trasportatore.h"


char *Trasportatore::getStatus(int idOrdine, Con2DB db1){

    PGresult *res;
    char sqlcmd[1000];
    char *status;
    
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, 
            "SELECT statusAcq FROM Acquisto WHERE (idAcq = \'%d\')", idOrdine);
    res = db1.ExecSQLtuples(sqlcmd);
    status = PQgetvalue(res, 0, PQfnumber(res, "statusAcq"));
    PQclear(res);
   
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    return status;
}