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

    const char *name;
    const char *cognome;
    const char *email;
    const char *password;
    const char *purchType;
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


    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "SELECT idc FROM Costumer");
    res = db.ExecSQLtuples(sqlcmd);
    idc = atoi(PQgetvalue(res, 0, PQfnumber(res, "idc")));
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    Costumer costumer(name, cognome, email);

    //test oggetto non trovato

    costumer.ricerca("Kindle", 1, lista, db);

    //fine test

    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "SELECT * FROM Oggetto WHERE ido = \'%d\'", 1);
    res = db.ExecSQLtuples(sqlcmd);
    nomeOgg = PQgetvalue(res, 0, PQfnumber(res, "nameo"));
    descrizioneOgg = PQgetvalue(res, 0, PQfnumber(res, "descr"));
    barCodeOgg = PQgetvalue(res, 0, PQfnumber(res, "cbar"));
    categoriaOgg = PQgetvalue(res, 0, PQfnumber(res, "category"));
    PQclear(res);

    strcpy(NomeOggprov, nomeOgg);

    sprintf(sqlcmd, "SELECT idt FROM Trasportatore");
    res = db.ExecSQLtuples(sqlcmd);
    idtrasp = atoi(PQgetvalue(res, 0, PQfnumber(res, "idt")));
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    //test quantità non suff

    costumer.ricerca(NomeOggprov, 500, lista, db);

    //fine test

    int quantity = (rand() %15)+1;
    costumer.ricerca(NomeOggprov, quantity, lista, db);
    cout << endl;
    cout << "----------------------------------------------------------------" << endl << endl;

    const char *idInv = lista[0][0].c_str();

    if (strcmp(idInv, ctrlValue) != 0){
        
        pid = getpid();

        printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);
        c2r = redisConnect("localhost", 6379);
        printf("main(): pid %d: user %s: connected to redis\n", pid, username);

        costumer.acquisto(idInv, idc, idtrasp, quantity, db);


        initStreams(c2r, WRITE_STREAM);
        initStreams(c2r, READ_STREAM);

        double elapsedMs = 0.0;
        double ReadElapsedMs = 0.0;

        sendMsg(c2r, reply, WRITE_STREAM, key, value, elapsedMs);

        cout << "Nuovo ordine creato: \n\tId Prodotto: " << idInv <<  "\n\tQuantità: " << quantity << endl;

        string strElapsedMs = to_string(elapsedMs); 
        char const *elap = strElapsedMs.c_str();

        sprintf(sqlcmd, "BEGIN"); 
        res = db.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd,
        "INSERT INTO LogSender VALUES(DEFAULT, now(), \'%d\', \'%d\', \'%d\', \'%s\') ON CONFLICT DO NOTHING",
        pid, idc, idtrasp, elap);
        res = db.ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = db.ExecSQLcmd(sqlcmd);
        PQclear(res);

        while(1){
            readMsg(c2r, reply, READ_STREAM, username, ReadElapsedMs);

            string strReadElapsedMs = to_string(ReadElapsedMs); 
            char const *elapRead = strReadElapsedMs.c_str();

            sprintf(sqlcmd, "BEGIN"); 
            res = db.ExecSQLcmd(sqlcmd);
            PQclear(res);

            sprintf(sqlcmd,
            "INSERT INTO LogReader VALUES(DEFAULT, now(), \'%d\', \'%d\', \'%s\') ON CONFLICT DO NOTHING",
            pid, idc, elapRead);
            res = db.ExecSQLcmd(sqlcmd);
            PQclear(res);

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