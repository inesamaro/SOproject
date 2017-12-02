#include "header.h"

void atendimento() {
  Paciente paciente; // = (Paciente)malloc(sizeof(struct paciente));
  if (msgrcv(mqid, &paciente, sizeof(paciente)-sizeof(long), -3, 0) == -1){
	perror("Oh boy u got a error recieving a msg from the messagequeue");
  }

  printf("-----------------------------------> %s, %ld\n",paciente.info.nome, paciente.mtype);
  //shared_var->nAtendidos += 1; //nao está a incrementar bem a shared_var

  //printf("numero de pessoas atendidas: %d \n", (shared_var)->nAtendidos);
}

void criarDoutor() {
  int i;
  for (i=0; i<5/*config->nDoutores*/; i++) {
    if (fork() == 0) {
      printf("[%d] INICIO DOUTOR\n", getpid());
      atendimento();//por fazer
      printf("[%d] FIM DOUTOR\n", getpid());
      exit(0);
    }
  }

  int rc;
  struct msqid_ds buf;
  int num_pacientes;

  while(1){ //sempre que um dos processos morre um novo é criado
      wait(NULL);
      msgctl(mqid, IPC_STAT, &buf);
      num_pacientes = buf.msg_qnum;
      printf("numero de pacientes na queue: %d\n", num_pacientes);
      if (num_pacientes > 0) {
        if(fork() == 0){
          printf("[%d] NEW INICIO DOUTOR\n", getpid());
          atendimento(); //por fazer
          printf("[%d] NEW FIM DOUTOR\n", getpid());
          exit(0);
        }
      }
    }
 //de momento manter comentado para nao criar demasiados doutores
}
