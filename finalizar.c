#include "header.h"

void finalizar(Config *config, int shmid) {
  int i;
  for(i = 0; i<config->nDoutores; i++){
    //printf("%d\n", configuration_array[1]);
    wait(NULL);
  }
  //terminate(); esta funcao ainda nao esta adicionada ao header e ao makefile
  exit(0);
}
