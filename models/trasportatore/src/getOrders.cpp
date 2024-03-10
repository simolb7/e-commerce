#include <main.h>

// La funzione getOrders recupera gli ordini associati a un trasportatore dal database.
// Prende in input:
// - idT: l'ID del trasportatore.
// - db1: un oggetto della classe Con2DB utilizzato per l'accesso al database.
// - orders: un array in cui verranno memorizzati gli ID degli ordini associati al trasportatore.
void Trasportatore::getOrders(int idT, Con2DB db1, int orders[]){

    PGresult *res;
    char sqlcmd[1000];
    int row;
    
    // Inizio transazione
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Esegue la query per recuperare gli ID degli ordini associati al trasportatore
    sprintf(sqlcmd, 
            "SELECT idAcq FROM Acquisto WHERE (trasportatore = \'%d\')", idT);
    res = db1.ExecSQLtuples(sqlcmd);
    row = PQntuples(res);
    for(int i = 0; i < row; i++){
        int val = atoi(PQgetvalue(res, i, PQfnumber(res, "idAcq")));
        orders[i] = val;
    }
    PQclear(res);
    
    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

};
