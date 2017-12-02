#include "header.h"

void atendimento() {
  Paciente *paciente;
  printf("entrei no atendimento\n");
  if (msgrcv(mqid, &paciente, sizeof(paciente)-sizeof(long), -3, 0) == -1){
	perror("Oh boy u got a error recieving a msg from the messagequeue");
  }

  printf("prioridade no recv %ln\n", &paciente->mtype);
  printf("mqid no recv %d\n", mqid);
  printf("Paciente a ser tratado: %s, %ld \n",paciente->nome, paciente->mtype);
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
}

  /*while(1){ //sempre que um dos processos morre um novo é criado
    wait(NULL);
    if(!(id = fork())){
      printf("[%d] INICIO DOUTOR\n", getpid());
      doutor(config, shared_var); //por fazer
      printf("[%d] FIM DOUTOR\n", getpid());
      exit(0);
    }
  } //de momento manter comentado para nao criar demasiados doutores
}*/
