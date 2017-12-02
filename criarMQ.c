#include "header.h"

//Criaçao da message message queue
void criarMQ(){
  if ((mqid = msgget(IPC_PRIVATE, IPC_CREAT|0777)) < 0) {
    perror("Error creating message queue");
  }
  else{
    printf("-------------> message queue criada\n");
  }
}
