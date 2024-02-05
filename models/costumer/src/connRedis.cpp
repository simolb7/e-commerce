#include <main.h>
using namespace std;
#define READ_STREAM "stream2"
#define WRITE_STREAM "stream1"

int main() {
    redisContext *c2r;
    redisReply *reply;

    int pid;
    unsigned seed;
    char key1[100];
    char value1[100];
    char username[100];
    bool cond;

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

    
}