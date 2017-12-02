#include "header.h"

//Por o paciente na message queue
void sendMQ(Paciente* paciente){
  int msgsend;
  if ((msgsend = msgsnd(mqid, &paciente, sizeof(paciente)-sizeof(long), 0)) == -1){
    perror("Oh boy u got a error sending a msg to the messagequeue");
  }
  else {
  	printf("prioridade no send %ld\n", paciente->mtype);
  	printf("mqid no send %d\n", mqid); 
    	printf("o paciente ---> %s <--- entrou na mq\n", paciente->nome);
  }
}
