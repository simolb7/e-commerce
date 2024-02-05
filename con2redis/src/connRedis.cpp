#include <main.h>

int block = 1000000000;
char *msgid;
char *fval;

void sendMsg(redisContext *c2r, redisReply *reply, char const *stream, char const *key, char const *value){
    reply = RedisCommand(c2r, "XADD %s * %s %s", WRITE_STREAM, key, value);
    assertReplyType(c2r, reply, REDIS_REPLY_STRING);
    freeReplyObject(reply);
};

char const * readMsg(redisContext *c2r, redisReply *reply, char *stream, char const *username) {
    reply = RedisCommand(c2r, "XREADGROUP GROUP diameter %s BLOCK %d COUNT 2 NOACK STREAMS %s >", 
                        username, block, READ_STREAM);
    //verifica che ci sia stata una risposta
    assertReply(c2r, reply);
    //mostra la risposta e indenta rispetto al valore della colonna (0)
    dumpReply(reply, 0);
    for (int k=0; k < ReadNumStreams(reply); k++) {
        //inserisce in streamname, il nome della stream prendendola dalla risposta
        ReadStreamName(reply, stream, k);
        //cicla in base al numero di messaggi della risposta in questione nel for precedente
        for (int i=0; i < ReadStreamNumMsg(reply, k); i++) {
            //inserisce in msgid l'id del messaggio analizzato
            ReadStreamNumMsgID(reply, k, i, msgid);
            //for per iterare negli elementi del messaggio singolo (coppia chiave-valore)
            for (int h = 0; h < ReadStreamMsgNumVal(reply, k, i); h++) {
                //legge il messaggio singolo dall'array con indice [h] e lo mette in fval 
                ReadStreamMsgVal(reply, k, i, h, fval);
                printf("Nuovo ordine ricevuto: user %s: streamnum %d, msg %d, msgid %s value %d = %s\n", username, k, i, msgid, h, fval);
            }	      	      
        }
    }
    return fval;
}