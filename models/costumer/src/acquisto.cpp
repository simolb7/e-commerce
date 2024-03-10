#include <main.h>

// La funzione acquisto esegue l'acquisto di un prodotto da parte di un cliente.
// Prende in input:
// - idInv: un puntatore a una stringa rappresentante l'ID dell'inventario.
// - idCost: un intero rappresentante l'ID del cliente che effettua l'acquisto.
// - idTrasp: un intero rappresentante l'ID del trasportatore.
// - quantita: un intero rappresentante la quantità del prodotto acquistato.
// - db1: un oggetto della classe Con2DB utilizzato per l'accesso al database.
void Costumer::acquisto(const char * idInv, int idCost, int idTrasp, int quantita, Con2DB db1){

    int idA;
    int row;
    int qAtt;
    int qAgg;
    PGresult *res;
    char sqlcmd[1000];

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Inserisce l'acquisto nella tabella Acquisto
    sprintf(sqlcmd,
    "INSERT INTO Acquisto VALUES (DEFAULT, 'in preparazione', now(), \'%d\', \'%d\') ON CONFLICT DO NOTHING", idCost, idTrasp);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Ottiene la quantità attuale dall'inventario
    sprintf(sqlcmd,
    "SELECT quantitaAtt FROM Inventario WHERE (idInv = \'%s\')", idInv);
    res = db1.ExecSQLtuples(sqlcmd);
    qAtt = atoi(PQgetvalue(res, 0, PQfnumber(res, "quantitaAtt")));
    PQclear(res);

    // Ottiene l'ID da acquisto
    sprintf(sqlcmd,
    "SELECT idAcq FROM Acquisto");
    res = db1.ExecSQLtuples(sqlcmd);
    row = PQntuples(res);
    idA = atoi(PQgetvalue(res, row-1, PQfnumber(res, "idAcq")));
    PQclear(res);

    // Inserisce il prodotto acquistato nella tabella AcqInv
    sprintf(sqlcmd,
    "INSERT INTO AcqInv VALUES (\'%s\', \'%d\', \'%d\' )", idInv, idA, quantita);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Calcola la nuova quantità attuale nell'inventario
    qAgg = qAtt - quantita;

    // Aggiorna la quantità attuale nell'inventario
    sprintf(sqlcmd,
    "UPDATE Inventario SET quantitaAtt = \'%d\' WHERE (idInv = \'%s\')", qAgg, idInv);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Stampa un messaggio di successo
    cout << "Acquisto avvenuto con successo" << endl;

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};