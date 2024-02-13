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

    char const *name2 = "Luigi";
    char const *surname2 = "Verdi";
    char const *email2 = "luigiverdi420@gmail.com";
    char const *password2 = "forzapergolettese";
    char const *purchType2 = "Carta di credito";
    char const *ruolo2 = "Costumer";

    char const *name3 = "Stefania";
    char const *surname3 = "Bianchi";
    char const *email3 = "stefaniabianchi88@gmail.com";
    char const *password3 = "grandipalle22";
    char const *purchType3 = "Carta di credito";
    char const *ruolo3 = "Trasportatore";

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
    Utente utente2(name2, surname2, email2, password2, purchType2);
    Utente utente3(name3, surname3, email3, password3, purchType3);

    utente.registration(utente, db, ruolo);
    utente2.registration(utente2, db, ruolo2);
    utente3.registration(utente3, db, ruolo3);

    utente.login(utente, db);
    utente2.login(utente2, db);
    utente3.login(utente3, db);

    return 0;
};