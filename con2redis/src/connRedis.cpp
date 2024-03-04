#include "con2redis.h"
#include "local.h"
#include <chrono>
#include <iostream>


int block = 1000000000;
char fval[100];

void sendMsg(redisContext *c2r, redisReply *reply, char const *stream, char const *key, char *value, double& elapsedMs){

    auto start = std::chrono::steady_clock::now();

    reply = RedisCommand(c2r, "XADD %s * %s %s", stream, key, value);
    assertReplyType(c2r, reply, REDIS_REPLY_STRING);
    freeReplyObject(reply);

    auto end = std::chrono::steady_clock::now();

    auto elapsedNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    elapsedMs = elapsedNs / 1000000.0;
    
};

char *readMsg(redisContext *c2r, redisReply *reply, char const *stream, char const *username, double &ReadElapsedMs) {

    auto start = std::chrono::steady_clock::now();
    reply = RedisCommand(c2r, "XREADGROUP GROUP diameter %s BLOCK %d COUNT 2 NOACK STREAMS %s >", username, block, stream);
    //verifica che ci sia stata una risposta
    assertReply(c2r, reply);
    //mostra la risposta e indenta rispetto al valore della colonna (0)
    dumpReply(reply, 0);
    for (int k=0; k < ReadNumStreams(reply); k++) {
        //inserisce in streamname, il nome della stream prendendola dalla risposta
        //cicla in base al numero di messaggi della risposta in questione nel for precedente
        for (int i=0; i < ReadStreamNumMsg(reply, k); i++) {
            //inserisce in msgid l'id del messaggio analizzato
            //for per iterare negli elementi del messaggio singolo (coppia chiave-valore)
            int n = ReadStreamMsgNumVal(reply, k, i);
            for (int h = 1; h < n; h++) {
                //legge il messaggio singolo dall'array con indice [h] e lo mette in fval 
                ReadStreamMsgVal(reply, k, i, h, fval);
            }	      	      
        }
    }

    auto end = std::chrono::steady_clock::now();

    auto elapsedNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ReadElapsedMs = elapsedNs / 1000000.0;
    return fval;
}