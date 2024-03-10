#include <main.h>
#include <fornitore.h>

// La funzione addQuantity aggiunge una quantità specificata di un determinato oggetto all'inventario di un fornitore nel database.
// Prende in input:
// - oggetto1: un oggetto della classe Oggetto che rappresenta l'oggetto da aggiungere all'inventario.
// - fornitore1: un oggetto della classe Fornitore che rappresenta il fornitore dell'oggetto.
// - db1: un oggetto Con2DB che gestisce la connessione al database.
// - aggiunta: un intero rappresentante la quantità di oggetti da aggiungere all'inventario.
void Fornitore::addQuantity(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1, int aggiunta){
    char const *emailF = fornitore1.getEmail();
    char const *BarCodeOg = oggetto1.getBarCodeO();
    int idFor;
    int idOgg;
    int qAtt;
    int idInv;
    int pid;
    char const *controllo;
    char const *t = "t";
    PGresult *res;
    char sqlcmd[1000];

    pid = getpid();

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Otteniamo l'ID del fornitore
    sprintf(sqlcmd,
    "SELECT idU FROM Utente WHERE (emailU = \'%s\')", emailF);
    res = db1.ExecSQLtuples(sqlcmd);
    idFor = atoi(PQgetvalue(res, 0, PQfnumber(res, "idU")));
    PQclear(res);

    // Otteniamo l'ID dell'oggetto
    sprintf(sqlcmd,
    "SELECT idO FROM Oggetto WHERE (CBar = \'%s\')", BarCodeOg);
    res = db1.ExecSQLtuples(sqlcmd);
    idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
    PQclear(res);

    // Otteniamo l'ID e la quantità attuale dell'inventario del fornitore per l'oggetto specificato
    sprintf(sqlcmd,
    "SELECT idInv, quantitaatt FROM Inventario WHERE (Fornitore = \'%d\' AND Oggetto = \'%d\')", idFor, idOgg);
    res = db1.ExecSQLtuples(sqlcmd);
    idInv = atoi(PQgetvalue(res, 0, PQfnumber(res, "idInv")));
    qAtt = atoi(PQgetvalue(res, 0, PQfnumber(res, "quantitaatt")));
    PQclear(res);

    // Aggiorniamo la quantità attuale nell'inventario
    qAtt += aggiunta;
    sprintf(sqlcmd,
    "UPDATE Inventario SET quantitaatt = \'%d\' WHERE (Fornitore = \'%d\' AND Oggetto = \'%d\')", qAtt, idFor, idOgg);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Registriamo l'operazione di aggiunta nel log
    sprintf(sqlcmd,
    "INSERT INTO LogAggiunta VALUES (DEFAULT, now(), \'%d\', \'%d\', '%d\') ON CONFLICT DO NOTHING", pid, idInv, aggiunta);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    cout << "\t\tAggiunta di " << aggiunta << " prodotti all'inventario"<< endl;
    
    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};