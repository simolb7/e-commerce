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

    const char *name;
    const char *cognome;
    const char *email;
    const char *password;
    const char *purchType;

    char const *nomeOgg;
    char const *descrizioneOgg;
    char const *barCodeOgg;
    char const *categoriaOgg;
    char *lista[30][4];



    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "SELECT idc FROM Costumer");
    res = db.ExecSQLtuples(sqlcmd);
    idc = atoi(PQgetvalue(res, 0, PQfnumber(res, "idc")));
    PQclear(res);


    sprintf(sqlcmd, "SELECT * FROM Utente WHERE idU = \'%d\'", idc);
    res = db.ExecSQLtuples(sqlcmd);
    name = PQgetvalue(res, 0, PQfnumber(res, "nameU"));
    cognome = PQgetvalue(res, 0, PQfnumber(res, "surnameU"));
    email = PQgetvalue(res, 0, PQfnumber(res, "emailU"));
    password = PQgetvalue(res, 0, PQfnumber(res, "passwordU"));
    purchType = "PayPal";
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

    cout << nomeOgg << endl;
    cout << descrizioneOgg << endl;
    cout << barCodeOgg << endl;
    cout << categoriaOgg << endl;

    cout << endl;

    for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 4; ++j) {
                cout << lista[i][j] << " ";
            }
            cout << endl;
        }

    costumer.ricerca(nomeOgg, 1, lista, db);

    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << lista[i][j] << " ";
        }
        cout << endl;
    }

    
    costumer.acquisto(lista[0][0], costumer, 1, db);

    /*
    //char const *nomeOgg = "Mouse Logitech";
    char const *nomeOgg = "Monitor LG";
    char const *descrizioneOgg = "grandi palle, bel pisello";
    char const *barCodeOgg = "12345678900987654321";
    //char const *barCodeOgg = "12345678900987654322";
    char const *categoriaOgg = "Elettronica";

    char const *name = "Luigi";
    char const *surname = "Verdi";
    char const *email = "luigiverdi420@gmail.com";
    char const *password = "forzapergolettese";
    char const *purchType = "Carta di credito";
    char const *ruolo = "Costumer";
    
    costumer.ricerca(nomeOgg, 5, lista, db);

    costumer.acquisto(lista[0][0], costumer, 3, db);

    */

    /*

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
    */

    
    return 0;
};