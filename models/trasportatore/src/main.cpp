#pragma once
#include <main.h>
#include "trasportatore.h"

#define READ_STREAM "fornitore2trasportatore"
#define WRITE_STREAM "trasportatore2costumer"

int main(){
    redisContext *c2r;
    redisReply *reply;

    int pid;
    char *key = "key Trasportatore";
    char *value = "Aggiornamento stato spedizione";
    char *username = "trasportatore@gmail.com";
    char *fval;

    pid = getpid();
    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user %s: connected to redis\n", pid, username);

    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);

    fval = readMsg(c2r, reply, READ_STREAM, username);
    printf("result fval : %s", fval);
    
    sendMsg(c2r, reply, WRITE_STREAM, key, value);
    
    
    redisFree(c2r);
}