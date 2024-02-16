#include <main.h>

#define READ_STREAM "fornitore2trasportatore"
#define WRITE_STREAM "trasportatore2costumer"

int main(){
    
    redisContext *c2r;
    redisReply *reply;

    int pid;
    char const *key = "key Trasportatore";
    char const *value = "Aggiornamento stato spedizione";
    char const *username = "trasportatore@gmail.com";
    char const *fval;

    // db

    char const *name = "Stefania";
    char const *surname = "Bianchi";
    char const *email = "stefaniabianchi88@gmail.com";
    char const *password = "grandipalle22";
    char const *purchType = "Carta di credito";
    char const *ruolo = "Trasportatore";

    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    int ordini[10];

    Trasportatore trasportatore(name, surname, email, password, purchType);

    

    //redis

    pid = getpid();
    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user %s: connected to redis\n", pid, username);

    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);

    fval = readMsg(c2r, reply, READ_STREAM, username);
    printf("result fval : %s\n", fval);

    trasportatore.getOrders(trasportatore, db, ordini);

    int idO = ordini[0];
    
    sendMsg(c2r, reply, WRITE_STREAM, key, value);
    sleep(5);
    trasportatore.updateStatus(idO, db);
    sendMsg(c2r, reply, WRITE_STREAM, key, value);
    sleep(5);
    trasportatore.updateStatus(idO, db);
    sendMsg(c2r, reply, WRITE_STREAM, key, value);


    redisFree(c2r);
    return 0;
    
}