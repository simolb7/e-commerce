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
    char const *username = "luigiverdi420@gmail.com";
    PGresult *res;
    char sqlcmd[1000];
    int idc;
    int idtrasp;

    const char *name;
    const char *cognome;
    const char *email;
    const char *password;
    const char *purchType;

    char const *nomeOgg;
    char const *descrizioneOgg;
    char const *barCodeOgg;
    char const *categoriaOgg;
    string lista[30][4];



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

    Costumer costumer(name, cognome, email, password, purchType);

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

    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "SELECT idt FROM Trasportatore");
    res = db.ExecSQLtuples(sqlcmd);
    idtrasp = atoi(PQgetvalue(res, 0, PQfnumber(res, "idt")));
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    
    costumer.ricerca(nomeOgg, 1, lista, db);

    const char *idInv = lista[0][0].c_str();
 
    costumer.acquisto(idInv, idc, idtrasp, 1, db);
    

    pid = getpid();

    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user %s: connected to redis\n", pid, username);

    initStreams(c2r, WRITE_STREAM);
    initStreams(c2r, READ_STREAM);

    sendMsg(c2r, reply, WRITE_STREAM, key, value);

    while(1){
        readMsg(c2r, reply, READ_STREAM, username);
    };

    redisFree(c2r);
    

    
    return 0;
};