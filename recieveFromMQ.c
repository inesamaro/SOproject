#include "header.h"

//Envia o paciente da message queue para o doutor
void recieveFromMQ(#processoDoutor){
  int msgrecieved;
  if (msgrecieved = msgrcv(mqid, &processoDoutor, sizeof(Paciente), 1, -3) == -1){
    perror("Oh boy u got a error recieving a msg from the messagequeue");
  }
}
