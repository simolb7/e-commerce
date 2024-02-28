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

    statusAtt = trasportatore.getStatus(idO, db);
    char newValue1[100];
    strcpy(newValue1, value);
    strcat(newValue1, statusAtt);
    sendMsg(c2r, reply, WRITE_STREAM, key, newValue1);
    sleep(5);
    trasportatore.updateStatus(idO, db);

    statusAtt = trasportatore.getStatus(idO, db);
    char newValue2[100];
    strcpy(newValue2, value);
    strcat(newValue2, statusAtt);
    sendMsg(c2r, reply, WRITE_STREAM, key, newValue2);
    sleep(5);
    trasportatore.updateStatus(idO, db);

    statusAtt = trasportatore.getStatus(idO, db);
    char newValue3[100];
    strcpy(newValue3, value);
    strcat(newValue3, statusAtt);
    sendMsg(c2r, reply, WRITE_STREAM, key, newValue3);

    redisFree(c2r);
    return 0;
    
}