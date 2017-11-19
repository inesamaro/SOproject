#include "header.h"
void criarDoutores(Config *config/*, Estat *shared_var*/) {
  int i, id;


  for (i=0; i<config->nDoutores; i++) {
    if (fork() == 0) {
      printf("[%d] INICIO DOUTOR\n", getpid());
      doutor(config/*, shared_var*/); //por fazer
      printf("[%d] FIM DOUTOR\n", getpid());
      exit(0);
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
  }*/ //de momento manter comentado para nao criar demasiados doutores
}
