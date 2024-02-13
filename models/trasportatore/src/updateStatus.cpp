#include <main.h>
#include "trasportatore.h"

void Trasportatore::updateStatus(int idOrdine, Con2DB db1){
    //prende lo stato attuale dell'ordine dal db, e va al successivo
    // es:
    //   in preparazione -> in consegna e poi in consegna -> consegnato
    //   consegna -> X non è possibile andare oltre
    PGresult *res;
    char *status;
    getStatus(idOrdine, db1, status);
    char sqlcmd[1000];
    char *stato1 = "in preprazione";
    char *stato2 = "spedito";
    char *stato3 = "consegnato";
    
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
   
    if(strcmp(status, stato1) == 0){
        sprintf(sqlcmd, 
                "UPDATE Acquisto SET statusAcq = \'%s\' WHERE (idAcq = \'%d\')", stato2, idOrdine);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else if(strcmp(status, stato2) == 0){
        sprintf(sqlcmd, 
                "UPDATE Acquisto SET statusAcq = \'%s\' WHERE (idAcq = \'%d\')", stato3, idOrdine);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else if(strcmp(status, stato3) == 0){
        //DO NOTHING
    }

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);


}
