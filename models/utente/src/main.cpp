#include <main.h>
using namespace std;

#define WRITE_STREAM "customer2fornitore"
#define READ_STREAM "trasportatore2costumer"

//using namespace operazioni;

int main() {
    redisContext *c2r;
    redisReply *reply;

    //Con2DB db1("localost", "5432", "userdb", "47002", "ecommercedb");
    int pid;
    char *key = "key Costumer";
    char *value = "Nuovo ordine";
    char *username = "marcorossi69@gmail.com";



    char const *name = "Marco";
    char const *surname = "Rossi";
    char const *email = "marcorossi69@gmail.com";
    char const *password = "redigotham";
    char const *purchType = "Carta di credito";
    char const *ruolo = "Fornitore";

    pid = getpid();

    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user %s: connected to redis\n", pid, username);

    initStreams(c2r, WRITE_STREAM);
    initStreams(c2r, READ_STREAM);

    sendMsg(c2r, reply, WRITE_STREAM, key, value);
    redisFree(c2r);
    
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    Utente utente(name, surname, email, password, purchType);

    utente.registration(utente, db, ruolo);

    utente.login(utente, db);
    
    
   return 0;
};