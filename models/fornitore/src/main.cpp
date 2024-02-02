#include <main.h>

int main(){

    int pid;
    unsigned seed;
    redisContext *c2r;
    redisReply *reply;
    char username[100];
    int block = 1000000000;
    char streamname[100];
    char msgid[100];
    char fval[100];
    char key[100];
    char value[100];
    int i, k, h;

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
    bool cond = true;

    while(cond) {
        reply = RedisCommand(c2r, "XREADGROUP GROUP diameter %s BLOCK %d COUNT 2 NOACK STREAMS %s >", 
			  username, block, READ_STREAM);
        //verifica che ci sia stata una risposta
        assertReply(c2r, reply);
        //mostra la risposta e indenta rispetto al valore della colonna (0)
        printf("\nCULO\n");
        dumpReply(reply, 0);
        for (k=0; k < ReadNumStreams(reply); k++)
        {
            ReadStreamName(reply, streamname, k);
            for (i=0; i < ReadStreamNumMsg(reply, k); i++) {
                ReadStreamNumMsgID(reply, k, i, msgid);
                printf("main(): pid %d: user %s: stream %s, streamnum %d, msg %d, msgid %s with %d values\n",
                    pid, username, streamname, k, i, msgid, ReadStreamMsgNumVal(reply, k, i));
                for (h = 0; h < ReadStreamMsgNumVal(reply, k, i); h++)
                {
                    ReadStreamMsgVal(reply, k, i, h, fval);
                    printf("main(): pid %d: user %s: streamnum %d, msg %d, msgid %s value %d = %s\n", pid, username, k, i, msgid, h, fval);
                }	      	      
            }
        }
        freeReplyObject(reply);
        sprintf(key, "Risposta");
        sprintf(value, "%d", fval);
        reply = RedisCommand(c2r, "XADD %s * %s %s", WRITE_STREAM, key, value);
        //controlla il tipo della rispota che deve essere stringa
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        
        printf("main(): pid =%d: stream %s: Added %s -> %s (id: %s)\n", pid, WRITE_STREAM, key, value, reply->str);
        freeReplyObject(reply);
    }    
    redisFree(c2r);
};