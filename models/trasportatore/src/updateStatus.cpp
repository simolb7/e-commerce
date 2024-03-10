#include <main.h>

// La funzione updateStatus aggiorna lo stato di un ordine in base allo stato attuale.
// Prende in input:
// - idOrdine: l'ID dell'ordine di cui si desidera aggiornare lo stato.
// - db1: un oggetto della classe Con2DB utilizzato per l'accesso al database.
void Trasportatore::updateStatus(int idOrdine, Con2DB db1){
    PGresult *res;
    char sqlcmd[1000];
    const char *statusA;
    const char *stato1 = "in preparazione";
    const char *stato2 = "spedito";
    const char *stato3 = "consegnato";
    
    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Ottiene lo stato attuale dell'ordine
    sprintf(sqlcmd, 
            "SELECT statusAcq FROM Acquisto WHERE (idAcq = \'%d\')", idOrdine);
    res = db1.ExecSQLtuples(sqlcmd);
    statusA = PQgetvalue(res, 0, PQfnumber(res, "statusAcq"));
    PQclear(res);

    // Aggiorna lo stato in base allo stato attuale
    if(strcmp(statusA, stato1) == 0){
        sprintf(sqlcmd, 
                "UPDATE Acquisto SET statusAcq = \'%s\' WHERE (idAcq = \'%d\')", stato2, idOrdine);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else if(strcmp(statusA, stato2) == 0){
        sprintf(sqlcmd, 
                "UPDATE Acquisto SET statusAcq = \'%s\' WHERE (idAcq = \'%d\')", stato3, idOrdine);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } else if(strcmp(statusA, stato3) == 0){
        //DO NOTHING
    }

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};
