#include <main.h>
#include "costumer.h"

#define WRITE_STREAM "customer2fornitore"
#define READ_STREAM "trasportatore2costumer"

int main(){

    redisContext *c2r;
    redisReply *reply;

    int pid;
    char const *key = "key Costumer";
    char value[] = "Nuovo ordine";
    char const *username = "luigiverdi420@gmail.com";

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

    char * lista[10][4];

    Con2DB db("localhost", "5432", "userdb", "47002", "ecommercedb");

    Costumer costumer(name, surname, email, password, purchType);

    costumer.ricerca(nomeOgg, 5, lista, db);

    costumer.acquisto(lista[0][0], costumer, 3, db);

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