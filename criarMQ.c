#include "header.h"

//Criaçao da message message queue
int criarMQ(){
  int mqid;
  if ((mqid = msgget(IPC_PRIVATE, IPC_CREAT|0777)) < 0) {
    perror("Error creating message queue");
  }
  return mqid;
}
