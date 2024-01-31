#include <main.h>

using namespace std;
//using namespace operazioni;

int main() {
    //redisContext *c2r;
    //redisReply *reply;

    //Con2DB db1("localost", "5432", "userdb", "47002", "ecommercedb");
    int pid;
    unsigned seed;

    #if (DEBUG > 0)
        setvbuf(stdout, (char*) NULL, _IONBF, 0);
        setvbuf(stderr, (char*) NULL, _IONBF, 0);
    #endif

    seed = (unsigned) time(NULL);
    srand(seed);

    //sprintf(username, "%u", rand());

    pid = getpid();

    //printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);

    //c2r = redisConnect("localhost", 6379);

    //printf("main(): pid %d: user %s: connected to redis\n", pid, username);


    /* Create streams/groups */
    //initStreams(c2r, READ_STREAM);
    //initStreams(c2r, WRITE_STREAM);

    char const *name = "Marco";
    char const *surname = "Rossi";
    char const *email = "marcorossi69@gmail.com";
    char const *password = "redigotham";
    char const *purchType = "Carta di credito";

    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    Utente utente(name, surname, email, password, purchType);

    utente.registration(utente, db);

    /*while (1){


        usleep(1000);

    }*/
    
    //redisFree(c2r);

    return 0;

};
