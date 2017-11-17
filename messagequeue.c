typedef struct paciente *Node_paciente;
typedef struct paciente {
  int prioridade;
  long msgtype = prioridade;
  char nome[50];
  int numTriagem;
  int numAtend;
  clock_t inicio; //para calcularmos qunato tempo e que cada paciente gastou desde que entrou no sistema atá que saiu
  clock_t fim;
  Node_paciente next;
} Paciente;


//Cria a message queue que vai para o main
mqid = msgget(IPC_PRIVATE, IPC_CREAT|0777);
if (mqid < 0) {
  perror("Error creating message queue"):
}


//Insere o paciente na message queue
while(1){
  msgsend = msgsnd(mqid, &#nomepacient, sizeof(Paciente), 0);
  if (msgsend == -1){
    perror("Oh boy u got a error sending a msg to the messagequeue");
  }
}

//Ve qual o proximo paciente a ser atendido e envia o paciente para o processo doctor
while(true){
  msgrecieved = msgrcv(mqid, &processoDoutor?? , sizeof(Paciente), 1, -3);
  if (msgrecieved == -1){
    perror("Oh boy u got a error recieving a msg from the messagequeue");
  }
}

//Regista no log que o paciente foi atendido


//Remove message queue
msgctl(mqid, IPC_RMID);
