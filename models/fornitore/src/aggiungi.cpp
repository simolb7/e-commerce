
#include <main.h>
#include <fornitore.h>

// La funzione addOggetto aggiunge un nuovo oggetto al database.
// Prende in input:
// - oggetto1: un oggetto di tipo Oggetto.
// - db1: un oggetto della classe Con2DB utilizzato per l'accesso al database.
void Oggetto::addOggetto(Oggetto oggetto1, Con2DB db1){
    char const *nomeA = oggetto1.getNomeO();
    char const *descrizioneA = oggetto1.getDescrizioneO();
    char const *barCodeA = oggetto1.getBarCodeO();
    char const *categoriaA = oggetto1.getCategoriaO();
    PGresult *res;
    char sqlcmd[1000];

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Inserisci la categoria dell'oggetto
    sprintf(sqlcmd,
    "INSERT INTO Categoria VALUES (DEFAULT, \'%s\') ON CONFLICT DO NOTHING", categoriaA);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Inserisci l'oggetto nel database
    sprintf(sqlcmd,
    "INSERT INTO Oggetto VALUES (DEFAULT, \'%s\', \'%s\', \'%s\', 1) ON CONFLICT DO NOTHING", nomeA, descrizioneA, barCodeA);
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    cout << "\tScheda tecnica creata correttamente per il prodotto con barcode: " << barCodeA << endl;

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
};