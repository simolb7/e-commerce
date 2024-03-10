#include <main.h>
#include <fornitore.h>

// La funzione addInventario aggiunge un nuovo oggetto all'inventario del fornitore nel database.
// Se l'oggetto non esiste già nel database, lo aggiunge anche alla tabella degli oggetti.
// Prende in input:
// - oggetto1: un oggetto di tipo Oggetto.
// - fornitore1: un oggetto di tipo Fornitore.
// - db1: un oggetto della classe Con2DB utilizzato per l'accesso al database.
// - prezzo: il prezzo dell'oggetto.
// - quantity: la quantità di oggetti da aggiungere all'inventario.
void Fornitore::addInventario(Oggetto oggetto1, Fornitore fornitore1, Con2DB db1, float prezzo, int quantity){
    char const *emailF = fornitore1.getEmail();
    char const *BarCodeOg = oggetto1.getBarCodeO();
    int idFor;
    int idOgg;
    char const *controllo;
    char const *t = "t";
    PGresult *res;
    char sqlcmd[1000];

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Ottieni l'ID del fornitore tramite l'email
    sprintf(sqlcmd,
    "SELECT idU FROM Utente WHERE (emailU = \'%s\')", emailF);
    res = db1.ExecSQLtuples(sqlcmd);
    idFor = atoi(PQgetvalue(res, 0, PQfnumber(res, "idU")));
    PQclear(res);

    // Controlla se l'oggetto esiste nel database
    sprintf(sqlcmd,
    "SELECT EXISTS (SELECT idO FROM Oggetto WHERE (CBar = \'%s\'))", BarCodeOg);
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    // Se l'oggetto esiste già nel database
    if (strcmp(controllo, t) == 0){
        // Ottieni l'ID dell'oggetto
        sprintf(sqlcmd,
        "SELECT idO FROM Oggetto WHERE (CBar = \'%s\')", BarCodeOg);
        res = db1.ExecSQLtuples(sqlcmd);
        idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
        PQclear(res);

        // Aggiungi l'oggetto all'inventario se non esiste già
        sprintf(sqlcmd,
        "INSERT INTO Inventario VALUES (DEFAULT, \'%f\', \'%d\', \'%d\', now(), \'%d\', \'%d\') ON CONFLICT DO NOTHING", prezzo, quantity, quantity, idFor, idOgg);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        cout << "\tProdotto aggiunto correttamente nell'inventario per l'oggetto con barcode: "<< BarCodeOg << endl;

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    // Se l'oggetto non esiste già nel database
    } else {
        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        cout << "\tScheda tecnica non trovata, creazione dell'oggetto in corso..." << endl;

        // Aggiunge l'oggetto al database
        oggetto1.addOggetto(oggetto1, db1);

        // Inizio transazione
        sprintf(sqlcmd, "BEGIN"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        // Ottieni l'ID dell'oggetto appena aggiunto
        sprintf(sqlcmd,
        "SELECT idO FROM Oggetto WHERE (CBar = \'%s\')", BarCodeOg);
        res = db1.ExecSQLtuples(sqlcmd);
        idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
        PQclear(res);

        // Aggiungi l'oggetto all'inventario
        sprintf(sqlcmd,
        "INSERT INTO Inventario VALUES (DEFAULT, \'%f\', \'%d\', \'%d\', now(), \'%d\', \'%d\') ON CONFLICT DO NOTHING", prezzo, quantity, quantity, idFor, idOgg);
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        cout << "\tProdotto aggiunto correttamente nell'inventario per l'oggetto con barcode: "<< BarCodeOg << endl;

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    }
};