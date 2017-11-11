#include "header.h"

void finalizar(Config *config, int shmid) {
  int i;
  for(i = 0; i<config->nDoctors; i++){
    //printf("%d\n", configuration_array[1]);
    wait(NULL);
  }
  print_statistics();
  terminate();
  exit(0);
}
