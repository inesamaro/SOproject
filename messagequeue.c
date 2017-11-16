//Cria a message queue que vai para o main
mqid = msgget(IPC_PRIVATE, IPC_CREAT|0777);
if (mqid < 0) {
  perror("Error creating message queue"):
}

//Remove message queue
msgctl(mqid, IPC_RMID);

//Insere o paciente na message queue
msgsend = msgsnd(mqid, &#nomepacient, sizeof(Paciente), 0);
if (msgsend == -1){
  perror("Oh boy u got a error sending a msg to the messagequeue");
}

//Ve qual o proximo paciente a ser atendido por qual doctor
ordemParaMsgQueue(){

}


//Envia o paciente para o processo doctor
//msgrecieved = msgrcv(mquid, &#nomepacient??, sizeof(Paciente), 1, 0);
//if (msgrecieved == -1){
  //perror("Oh boy u got a error recieving a msg from the messagequeue")
//}

//Regista no log que o paciente foi atendido
