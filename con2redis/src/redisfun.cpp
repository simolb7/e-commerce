#include "con2redis.h"
#include "local.h"

// La funzione print_reply_types stampa i tipi di risposta disponibili nella libreria client di Redis.
void print_reply_types()
{
  printf("REDIS_REPLY_STRING=%d,\
REDIS_REPLY_STATUS=%d,\
REDIS_REPLY_INTEGER=%d,\
REDIS_REPLY_NIL=%d,\
REDIS_REPLY_ERROR=%d,\
REDIS_REPLY_ARRAY=%d\n",
	 REDIS_REPLY_STRING,
	 REDIS_REPLY_STATUS,
	 REDIS_REPLY_INTEGER,
	 REDIS_REPLY_NIL,
	 REDIS_REPLY_ERROR,
	 REDIS_REPLY_ARRAY
	 );
  
}

// La funzione assertReplyType controlla se il tipo di risposta ricevuta da Redis è quello atteso.
// Prende in input:
// - c: un puntatore a una struttura redisContext che rappresenta la connessione a Redis.
// - r: un puntatore a redisReply che conterrà la risposta di Redis.
// - type: il tipo di risposta atteso.
void assertReplyType(redisContext *c, redisReply *r, int type) {
    if (r == NULL)
        dbg_abort("NULL redisReply (error: %s)", c->errstr);
    if (r->type != type)
      { print_reply_types();
	dbg_abort("Expected reply type %d but got type %d", type, r->type);
      }
}


// La funzione assertReply verifica se la risposta ricevuta da Redis è nulla e termina il programma in caso affermativo.
// Prende in input:
// - c: un puntatore a una struttura redisContext che rappresenta la connessione a Redis.
// - r: un puntatore a redisReply che conterrà la risposta di Redis.
void assertReply(redisContext *c, redisReply *r) {
    if (r == NULL)
        dbg_abort("NULL redisReply (error: %s)", c->errstr);
}



// La funzione dumpReply stampa la risposta di Redis formattata.
// Prende in input:
// - r: un puntatore a redisReply che conterrà la risposta di Redis.
// - indent: un intero per l'indentazione della stampa.
void dumpReply(redisReply *r, int indent) {

    sds buffer = sdsempty();

    switch (r->type) {
        case REDIS_REPLY_STRING:
            buffer = sdscatfmt(buffer, "(string) %s\n", r->str);
            break;
        case REDIS_REPLY_STATUS:
            buffer = sdscatfmt(buffer, "(status) %s\n", r->str);
            break;
        case REDIS_REPLY_INTEGER:
            buffer = sdscatlen(buffer, "(integer) %lld\n", r->integer);
            break;
        case REDIS_REPLY_NIL:
            buffer = sdscatlen(buffer, "(nill)\n", 7);
            break;
        case REDIS_REPLY_ERROR:
            buffer = sdscatfmt(buffer, " (error) %s", r->str);
            break;
        case REDIS_REPLY_ARRAY:
            for (size_t i = 0; i < r->elements; i++) {
                dumpReply(r->element[i], indent + 2);
            }
            break;
        default:
            dbg_abort("Don't know how to deal with reply type %d", r->type);
    }

    if (sdslen(buffer) > 0) {
        for (int i = 0; i < indent; i++)
            printf(" ");

        printf("%s", buffer);
    }

    sdsfree(buffer);
}




void initStreams(redisContext *c, const char *stream) {
    redisReply *r = RedisCommand(c, "XGROUP CREATE %s diameter $ MKSTREAM", stream);
    assertReply(c, r);
    freeReplyObject(r);
}
