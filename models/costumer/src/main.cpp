#include <main.h>
#include "costumer.h"


#define WRITE_STREAM "customer2fornitore"
#define READ_STREAM "trasportatore2costumer"

int main(){

    redisContext *c2r;
    redisReply *reply;
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");


    int pid;
    char const *key = "key Costumer";
    char value[] = "Nuovo ordine";
    char const *username = "costumer";
    PGresult *res;
    char sqlcmd[1000];
    int idc;
    int idtrasp;

    /*
    const char *name;
    const char *cognome;
    const char *email;
    const char *password;
    const char *purchType;
    */
    char *NomeOggprov;

    char const *nomeOgg;
    char const *descrizioneOgg;
    char const *barCodeOgg;
    char const *categoriaOgg;
    
    string lista[30][4];
    char const *ctrlValue = "-1";

    for (int i = 0; i < 30; i++){
        lista[i][0] = "-1";
        lista[i][1] = "-1";
        lista[i][2] = "-1";
        lista[i][3] = "-1";
    }

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Ottiene l'id del customer
    sprintf(sqlcmd, "SELECT idc FROM Costumer");
    res = db.ExecSQLtuples(sqlcmd);
    idc = atoi(PQgetvalue(res, 0, PQfnumber(res, "idc")));
    PQclear(res);

    sprintf(sqlcmd, "SELECT * FROM Utente WHERE idu = \'%d\'", idc);
    res = db.ExecSQLtuples(sqlcmd);
    const char *name = PQgetvalue(res, 0, PQfnumber(res, "nameU"));
    const char *cognome = PQgetvalue(res, 0, PQfnumber(res, "surnameU"));
    const char *email = PQgetvalue(res, 0, PQfnumber(res, "emailU"));
    PQclear(res);

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);
    
    Costumer costumer(name, cognome, email);
    string emailCopy(email);
    // Prova ricerca oggetto che non esiste
    
    costumer.ricerca("Kindle", 1, lista, db);
    
    // Fine test

    // Inizio transazione
    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Ottengo le informazioni da Oggetto dove l'id è 1
    sprintf(sqlcmd, "SELECT * FROM Oggetto WHERE ido = \'%d\'", 1);
    res = db.ExecSQLtuples(sqlcmd);
    nomeOgg = PQgetvalue(res, 0, PQfnumber(res, "nameo"));
    descrizioneOgg = PQgetvalue(res, 0, PQfnumber(res, "descr"));
    barCodeOgg = PQgetvalue(res, 0, PQfnumber(res, "cbar"));
    categoriaOgg = PQgetvalue(res, 0, PQfnumber(res, "category"));
    PQclear(res);

    strcpy(NomeOggprov, nomeOgg);

    // Ottengo l'id del trasportatore
    sprintf(sqlcmd, "SELECT idt FROM Trasportatore");
    res = db.ExecSQLtuples(sqlcmd);
    idtrasp = atoi(PQgetvalue(res, 0, PQfnumber(res, "idt")));
    PQclear(res);

    // Chiude la transazione
    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);
    // Prova ricerca oggetto che esiste ma la cui quantità è insufficiente

    costumer.ricerca(NomeOggprov, 500, lista, db);

    // Fine test

    int quantity = (rand() %15)+1;
    costumer.ricerca(NomeOggprov, quantity, lista, db);

    cout << endl;
    cout << "----------------------------------------------------------------" << endl << endl;

    const char *idInv = lista[0][0].c_str();
    
    if (strcmp(idInv, ctrlValue) != 0){
        pid = getpid();
        // Connessione al server redis
        cout << "main(): pid " << pid << ": user " << emailCopy << ": connecting to redis..." << endl;
        c2r = redisConnect("localhost", 6379);
        cout << "main(): pid " << pid << ": user " << emailCopy << ": connected to redis" << endl;

        costumer.acquisto(idInv, idc, idtrasp, quantity, db);

        // Inizializzazione dei canali di lettura e scrittura per la comunicazione con Redis
        initStreams(c2r, WRITE_STREAM);
        initStreams(c2r, READ_STREAM);

        double elapsedMs = 0.0;
        double ReadElapsedMs = 0.0;

        // Manda un messaggio redis
        sendMsg(c2r, reply, WRITE_STREAM, key, value, elapsedMs);

        cout << "Nuovo ordine creato: \n\tId Prodotto: " << idInv <<  "\n\tQuantità: " << quantity << endl;

        string strElapsedMs = to_string(elapsedMs); 
        char const *elap = strElapsedMs.c_str();
        
        // Inizio transazione
        sprintf(sqlcmd, "BEGIN"); 
        res = db.ExecSQLcmd(sqlcmd);
        PQclear(res);

        // Crea un log del messaggio
        sprintf(sqlcmd,
        "INSERT INTO LogSender VALUES(DEFAULT, now(), \'%d\', \'%d\', \'%d\', \'%s\') ON CONFLICT DO NOTHING",
        pid, idc, idtrasp, elap);
        res = db.ExecSQLcmd(sqlcmd);
        PQclear(res);

        // Chiude la transazione
        sprintf(sqlcmd, "COMMIT"); 
        res = db.ExecSQLcmd(sqlcmd);
        PQclear(res);

        while(1){
            // Legge dalla stream redis
            readMsg(c2r, reply, READ_STREAM, username, ReadElapsedMs);

            string strReadElapsedMs = to_string(ReadElapsedMs); 
            char const *elapRead = strReadElapsedMs.c_str();

            // Inizio transazione
            sprintf(sqlcmd, "BEGIN"); 
            res = db.ExecSQLcmd(sqlcmd);
            PQclear(res);
            
            // Crea un log
            sprintf(sqlcmd,
            "INSERT INTO LogReader VALUES(DEFAULT, now(), \'%d\', \'%d\', \'%s\') ON CONFLICT DO NOTHING",
            pid, idc, elapRead);
            res = db.ExecSQLcmd(sqlcmd);
            PQclear(res);
            
            // Chiude la transazione
            sprintf(sqlcmd, "COMMIT"); 
            res = db.ExecSQLcmd(sqlcmd);
            PQclear(res);      
        };

            redisFree(c2r); 
    } else {
        redisFree(c2r);
    }

    return 0;
};