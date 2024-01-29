#include "con2redis.h"
#include "local.h"

#if 0
int ReadStreamName(redisReply *r, char *streamname)
{ 
  if ((r->type == REDIS_REPLY_ARRAY) && (r->elements == 1) )
     {
       r = r->element[0];
       if ((r->type == REDIS_REPLY_ARRAY) && (r->elements == 2) )
	 {
	   r = r->element[0];
           if (r->type == REDIS_REPLY_STRING)
	     {
	      strcpy(streamname, r->str);
	     }
	   else {fprintf(stderr, "ReadStreamName(): r -> type != REDIS_REPLY_STRING\n"); exit(-1);}
	 }
	else {fprintf(stderr, "ReadStreamName(): !((r->type == REDIS_REPLY_ARRAY) && (r->elements == 2)\n"); exit(-1);}  
     }
   else {fprintf(stderr, "ReadStreamName(): !((r->type == REDIS_REPLY_ARRAY) && (r->elements == 1) )\n"); exit(-1);}  

  return (0);
}
#endif


// reads k-th stream name
int ReadStreamName(redisReply *r, int indent, char *streamname,  long unsigned int k)
{

  strcpy(streamname, r->element[k]->element[0]->str);

  return(0);
  
#if (DEBUG > 1000)
  fprintf(stderr, "ReadStreamName(%d): Begin: k = %lu\n", indent, k);
#endif
 
 
    switch (r->type) {
    case REDIS_REPLY_STRING:  // stream name
#if (DEBUG > 1000)
      fprintf(stderr, "ReadStreamName(%d): REDIS_REPLY_STRING %s\n", indent, r->str);
#endif
 if (indent == 4)
   // stream name
   {
     strcpy(streamname, r->str);
     return (0);
   }
            break;

    case REDIS_REPLY_STATUS:
#if (DEBUG > 1000)
      fprintf(stderr, "ReadStreamName(%d): REDIS_REPLY_STATUS %s\n", indent, r->str);
#endif
       return (0);
            break;

    case REDIS_REPLY_INTEGER:
#if (DEBUG > 1000)
      fprintf(stderr, "ReadStreamName(%d): REDIS_REPLY_INTEGER %lld\n", indent, r->integer);
#endif
           return (0);
            break;

    case REDIS_REPLY_NIL:
#if (DEBUG > 1000)
      fprintf(stderr, "ReadStreamName(%d): REDIS_REPLY_NIL\n", indent);
#endif
           return (0);
            break;

    case REDIS_REPLY_ERROR:
#if (DEBUG > 1000)
	  fprintf(stderr, "ReadStreamName(%d): REDIS_REPLY_ERROR %s\n", indent, r->str);
#endif
      fprintf(stderr, "ReadStreamName(%d): REDIS_REPLY_ERROR %s\n", indent, r->str);
      exit(-1);
         break;

    case REDIS_REPLY_ARRAY:
#if (DEBUG > 1000)
	  fprintf(stderr, "ReadStreamName(%d): REDIS_REPLY_ARRAY %lu\n", indent, r->elements);
#endif
          if (indent <= 0)
	    {
              if (k <= r->elements)
		{ReadStreamName(r->element[k], indent + 2, streamname, k);}
	      else { fprintf(stderr, "ReadStreamName(%d): Error: k=%lu > r->elements=%lu\n", indent, k, r->elements); exit(-1);}
	    }
	  else // indent > 0
	    {
               ReadStreamName(r->element[0], indent + 2, streamname, k);
	    }
	  
            break;

     default:
            dbg_abort("Don't know how to deal with reply type %d", r->type);
    }

     return (0);
}  

// reads k-th stream name
int ReadStreamNumMsg(redisReply *r, long unsigned int streamnum)
{
  
  return(r->element[streamnum]->elements);

}  

// k-th stream, i-th msg id
int ReadStreamNumMsgID(redisReply *r, long unsigned int streamnum, int msgnum, char *msgid)
{

  strcpy(msgid, r->element[streamnum]->element[msgnum]->str);
  return(0);
}



// reads k-th stream name
int ReadNumStreams(redisReply *r)
{
  
return (r->elements);
  
#if (DEBUG > 1000)
  fprintf(stderr, "ReadNumStreams(): Begin\n");
#endif
 
 
    switch (r->type) {
    case REDIS_REPLY_STRING:  // stream name
#if (DEBUG > 1000)
      fprintf(stderr, "ReadNumStreams(): REDIS_REPLY_STRING %s\n", r->str);
#endif
           return (0);

            break;

    case REDIS_REPLY_STATUS:
#if (DEBUG > 1000)
      fprintf(stderr, "ReadNumStreams(): REDIS_REPLY_STATUS %s\n", r->str);
#endif
       return (0);
            break;

    case REDIS_REPLY_INTEGER:
#if (DEBUG > 1000)
      fprintf(stderr, "ReadNumStreams(): REDIS_REPLY_INTEGER %lld\n", r->integer);
#endif
           return (0);
            break;

    case REDIS_REPLY_NIL:
#if (DEBUG > 1000)
      fprintf(stderr, "ReadNumStreams(): REDIS_REPLY_NIL\n");
#endif
           return (0);
            break;

    case REDIS_REPLY_ERROR:
#if (DEBUG > 1000)
	  fprintf(stderr, "ReadNumStreams(): REDIS_REPLY_ERROR %s\n", r->str);
#endif
      fprintf(stderr, "ReadNumStreams(): REDIS_REPLY_ERROR %s\n", r->str);
      exit(-1);
         break;

    case REDIS_REPLY_ARRAY:
#if (DEBUG > 1000)
	  fprintf(stderr, "ReadNumStreams(): REDIS_REPLY_ARRAY %lu\n", r->elements);
#endif

	  return (r->elements);
	  
            break;

     default:
            dbg_abort("Don't know how to deal with reply type %d", r->type);
    }

     return (0);
}  



int ReadMsgID(redisReply *r, char *msgid)
{
  static int path_length = 4;
  static size_t branching[4] = {1, 2, 1, 2};
  static int child[4] = {0, 1, 0, 0};

  int i = 0;

  for (i = 0; i < path_length; i++)
    {
      if ((r->type != REDIS_REPLY_ARRAY) || (r->elements != branching[i]))
	{fprintf(stderr,
		 "ReadMsgID(): !((r->type == REDIS_REPLY_ARRAY) && (r->elements == %lu) )\n", branching[i]); exit(-1);
	  exit(-1);
	}  

      r = r->element[child[i]];
    }
  
  strcpy(msgid, r->str);

  return (0);
}  

/*  readstatus values:
0 : init
1 : expecting  stream name
2 : expecting  msg id
3 : expecting field value pair

*/

void ReadStreamReply(redisReply *r, int indent, int readstatus)
		    // char *status, char *streamname, char *msgid, char* *field, char* *value)
{
sds buffer = sdsempty();

#if (DEBUG > 1000)
 fprintf(stderr, "ReadStreamReply(%d): Begin\n", indent);
#endif
 
 
    switch (r->type) {
    case REDIS_REPLY_STRING:  // stream name
#if (DEBUG > 1000)
      fprintf(stderr, "ReadStreamReply(%d): REDIS_REPLY_STRING %s\n", indent, r->str);
#endif
 buffer = sdscatfmt(buffer, "(string) %s\n", r->str);
      //	    sprintf(streamname, "%s", buffer);
            break;
        case REDIS_REPLY_STATUS:
#if (DEBUG > 1000)
      fprintf(stderr, "ReadStreamReply(%d): REDIS_REPLY_STATUS %s\n", indent, r->str);
#endif
      buffer = sdscatfmt(buffer, "(status) %s\n", r->str);
	  //	    sprintf(status, "%s", buffer);
            break;
        case REDIS_REPLY_INTEGER:
#if (DEBUG > 1000)
      fprintf(stderr, "ReadStreamReply(%d): REDIS_REPLY_INTEGER %lld\n", indent, r->integer);
#endif
      buffer = sdscatlen(buffer, "(integer) %lld\n", r->integer);
	  // sprintf(msgid, "%s", buffer);
            break;
        case REDIS_REPLY_NIL:
#if (DEBUG > 1000)
      fprintf(stderr, "ReadStreamReply(%d): REDIS_REPLY_NIL\n", indent);
#endif
      buffer = sdscatlen(buffer, "(nill)\n", 7);
	  //  sprintf(status, "%s", buffer);
            break;
        case REDIS_REPLY_ERROR:
#if (DEBUG > 1000)
	  fprintf(stderr, "ReadStreamReply(%d): REDIS_REPLY_ERROR %s\n", indent, r->str);
#endif
      buffer = sdscatfmt(buffer, " (error) %s", r->str);
	  //    sprintf(status, "%s", buffer);
            break;
        case REDIS_REPLY_ARRAY:
#if (DEBUG > 1000)
	  fprintf(stderr, "ReadStreamReply(%d): REDIS_REPLY_ARRAY %lu\n", indent, r->elements);
#endif
	  for (size_t i = 0; i < r->elements; i++) {
	        readstatus = readstatus +1;
                ReadStreamReply(r->element[i], indent + 2, readstatus);
            }
            break;
        default:
            dbg_abort("Don't know how to deal with reply type %d", r->type);
    }

#if (DEBUG > 1000)
    fprintf(stderr, "ReadStreamReply(%d): buffer at end: %s\n", indent, buffer);
#endif

 if (sdslen(buffer) > 0) {
        for (int i = 0; i < indent; i++)
            printf(" ");

        printf("I=%d, readstatus=%d: %s", indent, readstatus, buffer);
    }

    sdsfree(buffer);
}

