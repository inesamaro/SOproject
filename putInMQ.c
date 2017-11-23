#include "header.h"

//Por o paciente na message queue
void putInMQ(Node_paciente paciente, int mqid){
  printf("Entrou na putInMQ\n");
  int msgsend;
  if ((msgsend = msgsnd(mqid, &paciente, sizeof(Paciente), 0)) == -1){
    perror("Oh boy u got a error sending a msg to the messagequeue");
  }
  printf("Fim da putInMQ\n");

}
