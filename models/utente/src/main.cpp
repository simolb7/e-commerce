#include <main.h>
using namespace std;

//using namespace operazioni;

int main() {
    redisContext *c2r;
    redisReply *reply;

    //Con2DB db1("localost", "5432", "userdb", "47002", "ecommercedb");
    int pid;
    unsigned seed;
    char key1[100];
    char value1[100];
    char username[100];
    bool cond;


    #if (DEBUG > 0)
        setvbuf(stdout, (char*) NULL, _IONBF, 0);
        setvbuf(stderr, (char*) NULL, _IONBF, 0);
    #endif

    char const *name = "Marco";
    char const *surname = "Rossi";
    char const *email = "marcorossi69@gmail.com";
    char const *password = "redigotham";
    char const *purchType = "Carta di credito";
    char const *ruolo = "Costumer";

    
    /*
    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    Utente utente(name, surname, email, password, purchType);

    utente.registration(utente, db, ruolo);

    utente.login(utente, db);
    */
    seed = (unsigned) time(NULL);
    srand(seed);
    sprintf(username, "%u", rand());  
    pid = getpid();
    
    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user %s: connected to redis\n", pid, username);
    reply = RedisCommand(c2r, "DEL %s", READ_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    reply = RedisCommand(c2r, "DEL %s", WRITE_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);
    cond = true;
    while (cond){
        sprintf(key1, "Stato");
        sprintf(value1, "Mi sono cagato addosso...");

        reply = RedisCommand(c2r, "XADD %s * %s %s", WRITE_STREAM, key1, value1);
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        printf("main(): pid =%d: stream %s: Added %s %s (id: %s)\n", pid, WRITE_STREAM, key1, value1, reply->str);
        freeReplyObject(reply);
        sleep(5);
        
        printf("\n");


    }
    redisFree(c2r);
};