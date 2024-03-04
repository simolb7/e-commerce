#include <main.h>

#define READ_STREAM "fornitore2trasportatore"
#define WRITE_STREAM "trasportatore2costumer"

int main(){
    
    redisContext *c2r;
    redisReply *reply;

    int pid;
    char const *key = "key Trasportatore";
    char const *value = "Stato spedizione: ";
    char const *username = "trasportatore@gmail.com";
    char const *fval;
    char *statusAtt;
    char const *statusConsegnato = "consegnato";
    int ordini[10]; //da rivedere
    PGresult *res;
    char sqlcmd[1000];
    int idt;
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");


    // db

    sprintf(sqlcmd, "BEGIN"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "SELECT idt FROM trasportatore");
    res = db.ExecSQLtuples(sqlcmd);
    idt = atoi(PQgetvalue(res, 0, PQfnumber(res, "idt")));
    PQclear(res);


    sprintf(sqlcmd, "SELECT * FROM Utente WHERE idU = \'%d\'", idt);
    res = db.ExecSQLtuples(sqlcmd);
    char const *name = PQgetvalue(res, 0, PQfnumber(res, "nameU"));
    char const *surname = PQgetvalue(res, 0, PQfnumber(res, "surnameU"));
    char const *email = PQgetvalue(res, 0, PQfnumber(res, "emailU"));
    char const *password = PQgetvalue(res, 0, PQfnumber(res, "passwordU"));
    char const *purchType = "PayPal";
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db.ExecSQLcmd(sqlcmd);
    PQclear(res);

    Trasportatore trasportatore(name, surname, email, password, purchType);

    pid = getpid();
    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, email);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user %s: connected to redis\n", pid, email);

    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);

    double ReadElapsedMs = 0.0;

    while(1){

        fval = readMsg(c2r, reply, READ_STREAM, username, ReadElapsedMs);
        printf("result fval : %s\n", fval);
        
        for (int i = 0; i < 10; ++i) {
            ordini[i] = -1; // Utilizzando -1 come valore speciale
        }

        trasportatore.getOrders(idt, db, ordini);

        double elasedMs= 0.0;
        

        for (int i = 0; i < 10; i++) {
            if (ordini[i] != -1){
                const char *check = trasportatore.getStatus(ordini[i], db);
                if (strcmp(check, statusConsegnato) != 0){
                    statusAtt = trasportatore.getStatus(ordini[i], db);
                    char newValue1[100];
                    strcpy(newValue1, value);
                    strcat(newValue1, statusAtt);
                    sendMsg(c2r, reply, WRITE_STREAM, key, newValue1, elasedMs);
                    sleep(5);
                    trasportatore.updateStatus(ordini[i], db);

                    statusAtt = trasportatore.getStatus(ordini[i], db);
                    char newValue2[100];
                    strcpy(newValue2, value);
                    strcat(newValue2, statusAtt);
                    sendMsg(c2r, reply, WRITE_STREAM, key, newValue2, elasedMs);
                    sleep(5);
                    trasportatore.updateStatus(ordini[i], db);

                    statusAtt = trasportatore.getStatus(ordini[i], db);
                    char newValue3[100];
                    strcpy(newValue3, value);
                    strcat(newValue3, statusAtt);
                    sendMsg(c2r, reply, WRITE_STREAM, key, newValue3, elasedMs);
                }
            } else {
                break;
            }
        }
    }


    redisFree(c2r);
    return 0;
    
}