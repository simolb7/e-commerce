#include <main.h>
#include <fornitore.h>

#define READ_STREAM "customer2fornitore"
#define WRITE_STREAM "fornitore2trasportatore"
#define DEBUG 1000

int main(){
    redisContext *c2r;
    redisReply *reply;

    int pid;
    char const *username = "fornitore@gmail.com";;
    char const *fval;
    char const *key = "key fornitore";
    char value[] = "Nuovo spedizione assegnata";

    //char const *nomeOgg = "Mouse Logitech";
    char const *nomeOgg = "Monitor LG";
    char const *descrizioneOgg = "grandi palle, bel pisello";
    char const *barCodeOgg = "12345678900987654321";
    //char const *barCodeOgg = "12345678900987654322";
    char const *categoriaOgg = "Elettronica";

    char const *name = "Marco";
    char const *surname = "Rossi";
    char const *email = "marcorossi69@gmail.com";
    char const *password = "redigotham";
    char const *purchType = "Carta di credito";
    char const *ruolo = "Costumer";

    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    
    Oggetto oggetto(nomeOgg, descrizioneOgg, barCodeOgg, categoriaOgg);

    oggetto.addOggetto(oggetto, db);

    Fornitore fornitore(name, surname, email, password, purchType);

    fornitore.addInventario(oggetto, fornitore, db);
    fornitore.addQuantity(oggetto, fornitore, db, 10);

#if (DEBUG > 0)
    printf("Diocan sono nel debug, enrico tronci esplode domani");

#endif

    pid = getpid();
    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user %s: connected to redis\n", pid, username);

    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);

    fval = readMsg(c2r, reply, READ_STREAM, username);
    printf("result fval : %s\n", fval);
    sendMsg(c2r, reply, WRITE_STREAM, key, value);

    redisFree(c2r);
    return 0;
};