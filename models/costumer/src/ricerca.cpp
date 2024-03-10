#include <main.h>

// La funzione ricerca esegue una ricerca di un oggetto nel database basata sul nome e sulla quantità richiesta.
// Prende in input:
// - nomeOg: una stringa rappresentante il nome dell'oggetto da cercare.
// - quantita: un intero rappresentante la quantità desiderata dell'oggetto.
// - result: un array bidimensionale di stringhe in cui memorizzare i risultati della ricerca.
// - db1: un oggetto Con2DB che gestisce la connessione al database.
void Costumer::ricerca(char const * nomeOg, int quantita, string result[30][4], Con2DB db1){
    PGresult *res;
    char sqlcmd[1000];
    int idOgg;
    int row;
    const char *controllo;
    const char *controllo2;
    const char *t = "t";

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN");
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Verifica se l'oggetto esiste nel database
    sprintf(sqlcmd,
    "SELECT EXISTS (SELECT idO FROM Oggetto WHERE (nameO = \'%s\'))", nomeOg);
    res = db1.ExecSQLtuples(sqlcmd);
    controllo = PQgetvalue(res, 0, PQfnumber(res, "exists"));
    PQclear(res);

    // Se l'oggetto esiste si prosegue
    if (strcmp(controllo, t) == 0){
        sprintf(sqlcmd,
        "SELECT idO FROM Oggetto WHERE (nameO = \'%s\')", nomeOg);
        res = db1.ExecSQLtuples(sqlcmd);
        idOgg = atoi(PQgetvalue(res, 0, PQfnumber(res, "idO")));
        PQclear(res);

        // Verifica se l'oggetto è disponibile nella quantità richiesta
        sprintf(sqlcmd,
        "SELECT EXISTS (SELECT idInv FROM Inventario WHERE (oggetto = \'%d\' AND QuantitaAtt >= \'%d\'))", idOgg, quantita);
        res = db1.ExecSQLtuples(sqlcmd);
        controllo2 = PQgetvalue(res, 0, PQfnumber(res, "exists"));
        PQclear(res);

        if (strcmp(controllo2, t) == 0){
            // Se l'oggetto è disponibile nella quantità richiesta, si procede con la ricerca dettagliata
            sprintf(sqlcmd,
            "SELECT idInv, prezzo, QuantitaAtt, fornitore FROM Inventario WHERE (oggetto = \'%d\' AND QuantitaAtt >= \'%d\')", idOgg, quantita);
            res = db1.ExecSQLtuples(sqlcmd);
            row = PQntuples(res);

            // Memorizza i risultati della ricerca nell'array bidimensionale result
            for (int i = 0; i < row; i++){
                char * idInv = PQgetvalue(res, i, PQfnumber(res, "idInv"));
                char * prezzo = PQgetvalue(res, i, PQfnumber(res, "prezzo"));
                char * quantitaAtt = PQgetvalue(res, i, PQfnumber(res, "QuantitaAtt"));
                char * fornitore = PQgetvalue(res, i, PQfnumber(res, "fornitore"));

                result[i][0] = idInv;
                result[i][1] = prezzo;
                result[i][2] = quantitaAtt;
                result[i][3] = fornitore;
            };
            PQclear(res);

            cout << "Oggetto trovato nella quantità desiderata" << endl;

            // Chiude la transazione
            sprintf(sqlcmd, "COMMIT");
            res = db1.ExecSQLcmd(sqlcmd);
            PQclear(res);  
        } else {
            cout << "Oggetto con nome: " << nomeOg << " non disponibile nella quantità desiderata"<< endl;

            // Chiude la transazione
            sprintf(sqlcmd, "COMMIT");
            res = db1.ExecSQLcmd(sqlcmd);
            PQclear(res);
            
        }  
    } else {
        cout << "Oggetto con nome: " << nomeOg << " non trovato"<< endl;

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT");
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);
    } 
};
