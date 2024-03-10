#include <main.h>
#include "trasportatore.h"

// La funzione getStatus restituisce lo stato di un ordine dato l'ID dell'ordine.
// Prende in input:
// - idOrdine: l'ID dell'ordine di cui si desidera ottenere lo stato.
// - db1: un oggetto della classe Con2DB utilizzato per l'accesso al database.
// Restituisce:
// - Una stringa rappresentante lo stato dell'ordine. Si consiglia di liberare la memoria allocata dopo l'uso.
char *Trasportatore::getStatus(int idOrdine, Con2DB db1){

    PGresult *res;
    char sqlcmd[1000];
    char *status;
    
    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Esegue la query per recuperare lo stato dell'ordine
    sprintf(sqlcmd, 
            "SELECT statusAcq FROM Acquisto WHERE (idAcq = \'%d\')", idOrdine);
    res = db1.ExecSQLtuples(sqlcmd);
    status = PQgetvalue(res, 0, PQfnumber(res, "statusAcq"));
    PQclear(res);
    
    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    return status;
}