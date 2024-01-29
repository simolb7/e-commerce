#include "con2redis.h"
#include "local.h"



int ReadNumStreams(redisReply *r)
{
  return (r->elements);  
}  


// reads k-th stream name
int ReadStreamName(redisReply *r, char *streamname,  long unsigned int k)
{
  strcpy(streamname, r->element[k]->element[0]->str);
  
  return(0); 
}  

// reads k-th stream name
int ReadStreamNumMsg(redisReply *r, long unsigned int streamnum)
{
  
  return(r->element[streamnum]->element[1]->elements);

}  

// k-th stream, i-th msg id
int ReadStreamNumMsgID(redisReply *r, long unsigned int streamnum, int msgnum, char *msgid)
{

  strcpy(msgid, r->element[streamnum]->element[1]->element[msgnum]->element[0]->str);
  return(0);
}


// k-th stream, i-th msg id
int ReadStreamMsgNumVal(redisReply *r, long unsigned int streamnum, int msgnum)
{

  return(r->element[streamnum]->element[1]->element[msgnum]->element[1]->elements);

}

// even entry field, odd entry field value
int ReadStreamMsgVal(redisReply *r, long unsigned int streamnum, int msgnum, int entry, char *value)
{

  strcpy(value, r->element[streamnum]->element[1]->element[msgnum]->element[1]->element[entry]->str);
  return(0);
}


