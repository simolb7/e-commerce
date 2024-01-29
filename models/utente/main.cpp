//
// Created by simolb on 1/29/24.
//

#include "main.h"

using namespace std;

int main() {
    redisContext *c2r;
    redisReply *reply;
    int pid;
    unsigned seed;

    #if (DEBUG > 0)
        setvbuf(stdout, (char*) NULL, _IONBF, 0);
        setvbuf(stderr, (char*) NULL, _IONBF, 0);
    #endif

    seed = (unsigned) time(NULL);
    srand(seed);

    sprintf(username, "%u", rand());

    pid = getpid();

    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);

    c2r = redisConnect("localhost", 6379);

    printf("main(): pid %d: user %s: connected to redis\n", pid, username);

    /* Create streams/groups */
    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);

    Utente utente = Utente(NAME,SURNAME,EMAIL,PASSWORD,PURCHTYPE);

    while (1){
        insulin_pump_state next_state = next(pump, c2r, t);


        usleep(1000);

        /* sleep   */
        //micro_sleep(1000000);
    }  // while ()

    redisFree(c2r);



}